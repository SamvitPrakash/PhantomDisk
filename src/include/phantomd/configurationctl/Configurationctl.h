#pragma once

#include <filesystem>
#include <toml++/toml.h>

class Configurationctl {
    private:
        std::filesystem::path CONFIG_FILE_PATH;
        toml::table CONFIG;
        
        bool validate(toml::table config) const;

    public:
        Configurationctl();
        Configurationctl(const std::filesystem::path& configFilePath);
        bool load();
        bool save();

        template<typename T>
        T meta(const std::string& key) const {
            const toml::table *meta = CONFIG["meta"].as_table();

            if(!meta->contains(key)){
                return T{};
            }

            return meta->get(key)->value<T>().value_or(T{});
        }

        template<typename T>
        T root(const std::string& key) const {
            const toml::table *root = CONFIG["root"].as_table();

            if(!root->contains(key)){
                return T{};
            }

            return root->get(key)->value<T>().value_or(T{});
        
        }

        template<typename T>
        T devices(std::size_t index, const std::string& key) const {
            const toml::array *devices = CONFIG["devices"].as_array();

            if(index >= devices->size()){
                return T{};
            }

            const toml::table *device = (*devices)[index].as_table();

            if(!device->contains(key)){
                return T{};
            }

            return device->get(key)->value<T>().value_or(T{});
        }

        template<typename T>
        bool setRoot(const std::string& key, const T& value){
            toml::table *root = CONFIG["root"].as_table();

            if(!root->contains(key)){
                return false;
            }

            (*root)[key] = value;
            return true;
        }

        template<typename T>
        bool setDevice(std::size_t index, const std::string& key, const T& value){
            toml::array *devices = CONFIG["devices"].as_array();

            if(index >= devices->size()){
                return false;
            }

            toml::table *device = (*devices)[index].as_table();

            if(!device->contains(key)){
                return false;
            }

            (*device)[key] = value;
            return true;
        }

        bool addDevice(const std::string& name, const std::string& physicalMount){
            toml::array *devices = CONFIG["devices"].as_array();

            toml::table newDevice;
            newDevice.insert("name", name);
            newDevice.insert("physical_mount", physicalMount);

            devices->push_back(newDevice);
            return true;
        }

        bool removeDevice(std::size_t index){
            toml::array *devices = CONFIG["devices"].as_array();

            if(index >= devices->size()){
                return false;
            }

            devices->erase(devices->begin() + index);
            return true;
        }

        ~Configurationctl();

};