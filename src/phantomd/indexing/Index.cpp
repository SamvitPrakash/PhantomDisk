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
        this->INDEX = toml::parse_file(path.string());
        this->DEVICE = this->INDEX["root"]["name"].value_or<std::string>("");
    } catch (const toml::parse_error& err) {
        throw std::runtime_error("Failed to parse configuration file: " + std::string(err.what()));
        
    }
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

bool Index::save() const {
    try {
        std::ofstream configFile(CONFIG_FILE_PATH);
        if (!configFile.is_open()) {
            throw std::runtime_error("Failed to open index file for writing.");
        }

        configFile << this->INDEX;
        configFile.close();

        return true;

    } catch (const std::exception& err) {
        throw std::runtime_error("Failed to save index file: " + std::string(err.what()));

        return false;
    }
}

toml::table* Index::index_at(size_t index) {
    toml::array *indexArray = this->INDEX["index"].as_array();

    if(index >= indexArray->size()){
        return nullptr;
    }

    return (*indexArray)[index].as_table();
}

toml::array* Index::index() {
    return this->INDEX["index"].as_array();
}

toml::table* Index::next_index() {
    toml::array *indexArray = this->INDEX["index"].as_array();
    toml::table *indexTable = (*indexArray)[this->ITERATOR_INDEX].as_table();

    if(this->ITERATOR_INDEX + 1 < indexArray->size()) this->ITERATOR_INDEX++;

    return indexTable;    
}

toml::table* Index::previous_index() {
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

    // (*indexArray)[index].as_table()->clear();
    indexArray->erase(indexArray->begin() + index);

    this->increment_root();

    return true;
}