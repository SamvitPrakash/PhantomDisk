#pragma once
#include <cstddef>
#include <string>
#include <toml++/toml.h>
#include <filesystem>

class Index {
    private:
        std::string DEVICE;
        toml::table INDEX;
        size_t ITERATOR_INDEX;
        std::filesystem::path CONFIG_FILE_PATH;
        
        void increment_root();
        bool save() const;
        
    public:

        Index(std::filesystem::path path);
        ~Index();
    
        std::chrono::system_clock::time_point get_last_updated() const;
        size_t current_index() const;
        int get_generation() const;
        std::string name() const;
        bool validate() const;
        
        toml::table* index_at(size_t index);
        toml::table* previous_index();
        toml::table* next_index();
        toml::array* index();
        
        bool update_index(size_t index, toml::table newIndex);
        bool add_index(toml::table index);
        bool remove_index(size_t index);

};