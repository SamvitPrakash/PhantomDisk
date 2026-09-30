#include "indexing/Index.h"
#include <cstddef>
#include <string>
#include <toml++/impl/array.hpp>
#include <toml++/impl/table.hpp>
#include <toml++/toml.h>
#include <stdexcept>

Index::Index(std::filesystem::path path) : ITERATOR_INDEX(0) {
    this->CONFIG_FILE_PATH = path;
    try{
        this->INDEX = toml::parse_file(path.string()+"/.index.toml");
        this->DEVICE = this->INDEX["root"]["name"].value_or<std::string>("");
    } catch (const toml::parse_error& err) {
        throw std::runtime_error("Failed to parse index file: " + std::string(err.what()));
        
    }
}

Index::Index(std::filesystem::path path, std::string name) : ITERATOR_INDEX(0) {
    this->CONFIG_FILE_PATH = path.string() + "/.index.toml";
    this->DEVICE = name;

    toml::table index;
    toml::table root;

    root.insert_or_assign("name", name);
    root.insert_or_assign("generation", 0);
    root.insert_or_assign("last_updated", std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    index.insert_or_assign("root", root);
    index.insert_or_assign("index", toml::array{});

    this->INDEX = index;

    this->save();

}

Index::~Index() {}

void Index::increment_root() {
    toml::table *root = INDEX["root"].as_table();
    root->insert_or_assign("generation", this->INDEX["root"]["generation"].value_or(0) + 1);
    root->insert_or_assign("last_updated", std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    this->save();
}

std::string Index::name() const {
    return this->DEVICE;
}

size_t Index::current_index() const {
    return this->ITERATOR_INDEX;
}

int Index::get_generation() const {
    return this->INDEX["root"]["generation"].value_or(0);
}

std::chrono::system_clock::time_point Index::get_last_updated() const {
    std::time_t lastUpdated = this->INDEX["root"]["last_updated"].value_or(std::time_t{0});
    return std::chrono::system_clock::from_time_t(lastUpdated);
}

void Index::save() const {
    try {
        std::ofstream configFile(CONFIG_FILE_PATH);
        if (!configFile.is_open()) {
            throw std::runtime_error("Failed to open index file for writing.");
        }

        configFile << this->INDEX;
        configFile.close();

    } catch (const std::exception& err) {
        throw std::runtime_error("Failed to save index file: " + std::string(err.what()));
    }
}

bool Index::validate() const {
    // META
    if(!this->INDEX.contains("root") || !this->INDEX["root"].is_table()) return false;
    if(!this->INDEX["root"].as_table()->contains("name") || !this->INDEX["root"]["name"].is_string()) return false;
    if(!this->INDEX["root"].as_table()->contains("generation") || !this->INDEX["root"]["generation"].is_integer()) return false;
    if(!this->INDEX["root"].as_table()->contains("last_updated") || !this->INDEX["root"]["last_updated"].is_integer()) return false;
    
    // INDEX
    if(!this->INDEX.contains("index") || !this->INDEX["index"].is_array()) return false;
    for(const auto& item : *this->INDEX["index"].as_array()){
        if(!item.is_table()) return false;
        const auto& table = *item.as_table();
        if(!table.contains("device") || !table["device"].is_string()) return false;
        if(!table.contains("logical_address") || !table["logical_address"].is_string()) return false;
        if(!table.contains("physical_address") || !table["physical_address"].is_string()) return false;
    }
    
    return true;
}

toml::array* Index::index() {
    return this->INDEX["index"].as_array();
}

toml::table* Index::index_at(size_t index) {
    if(index >= this->INDEX["index"].as_array()->size()) {
        return nullptr;
    }

    toml::array *indexArray = this->INDEX["index"].as_array();
    toml::table *indexTable = (*indexArray)[index].as_table();

    return indexTable;
}

toml::table* Index::next_index() {
    if(this->ITERATOR_INDEX >= this->INDEX["index"].as_array()->size()) {
        return nullptr;
    }

    toml::array *indexArray = this->INDEX["index"].as_array();
    toml::table *indexTable = (*indexArray)[this->ITERATOR_INDEX].as_table();

    if(this->ITERATOR_INDEX + 1 < indexArray->size()) this->ITERATOR_INDEX++;

    return indexTable;    
}

toml::table* Index::previous_index() {
    if(this->ITERATOR_INDEX >= this->INDEX["index"].as_array()->size()) {
        return nullptr;
    }

    toml::array *indexArray = this->INDEX["index"].as_array();
    toml::table *indexTable = (*indexArray)[this->ITERATOR_INDEX].as_table();
    
    if(this->ITERATOR_INDEX != 0) this->ITERATOR_INDEX--;

    return indexTable;
}

bool Index::update_index(size_t index, toml::table newIndex) {
    toml::array *indexArray = this->INDEX["index"].as_array();

    if(index >= indexArray->size()){
        return false;
    }

    toml::table *indexTable = (*indexArray)[index].as_table();
    *indexTable = newIndex;

    this->increment_root();
    
    return true;
}

bool Index::add_index(toml::table index) {
    toml::array *indexArray = this->INDEX["index"].as_array();
    indexArray->push_back(index);

    this->increment_root();

    return true;
}

bool Index::remove_index(size_t index) {
    toml::array *indexArray = this->INDEX["index"].as_array();

    if(index >= indexArray->size()){
        return false;
    }

    indexArray->erase(indexArray->begin() + index);

    this->increment_root();

    return true;
}