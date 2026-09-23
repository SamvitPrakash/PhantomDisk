#include "configurationctl/Configurationctl.h"

#include <stdexcept>
#include <toml++/impl/array.hpp>
#include <toml++/impl/table.hpp>

Configurationctl::Configurationctl(const std::filesystem::path& configFilePath) : CONFIG_FILE_PATH(configFilePath) {}

Configurationctl::Configurationctl() : CONFIG_FILE_PATH("config/config.toml") {}

Configurationctl::~Configurationctl() {}

bool Configurationctl::load() {
    try {
        this->CONFIG = toml::parse_file(CONFIG_FILE_PATH.string());
        if(!this->validate(this->CONFIG)) throw std::runtime_error("Configuration validation failed.");
            
        return true;
    } catch (const toml::parse_error& err) {
        throw std::runtime_error("Failed to parse configuration file: " + std::string(err.what()));
        return false;
    }
}

bool Configurationctl::save() {
    try {
        std::ofstream configFile(CONFIG_FILE_PATH);
        if (!configFile.is_open()) {
            throw std::runtime_error("Failed to open configuration file for writing.");
        }

        configFile << this->CONFIG;
        configFile.close();

        return true;
    } catch (const std::exception& err) {
        throw std::runtime_error("Failed to save configuration file: " + std::string(err.what()));
        return false;
    }
}

bool Configurationctl::validate(toml::table config) const {
    // META
    if (!config.contains("meta")) throw std::runtime_error("Missing 'meta' section in configuration.");
    if (!config["meta"].is_table()) throw std::runtime_error("'meta' section must be a table.");
    if (!config["meta"].as_table()->contains("version")) throw std::runtime_error("Missing 'version' key in 'meta' section.");
    if (!config["meta"].as_table()->contains("name")) throw std::runtime_error("Missing 'name' key in 'meta' section.");
    if (!config["meta"].as_table()->contains("description")) throw std::runtime_error("Missing 'description' key in 'meta' section.");
    if (!config["meta"].as_table()->contains("author")) throw std::runtime_error("Missing 'author' key in 'meta' section.");

    // ROOT
    if (!config.contains("root")) throw std::runtime_error("Missing 'root' section in configuration.");
    if (!config["root"].is_table()) throw std::runtime_error("'root' section must be a table.");
    if (!config["root"].as_table()->contains("retry_limit")) throw std::runtime_error("Missing 'retry_limit' key in 'root' section.");
    if (!config["root"].as_table()->contains("timeout_limit")) throw std::runtime_error("Missing 'timeout' key in 'root' section.");
    if (!config["root"].as_table()->contains("log_level")) throw std::runtime_error("Missing 'log_level' key in 'root' section.");
    if (!config["root"].as_table()->contains("logs")) throw std::runtime_error("Missing 'logs' key in 'root' section.");
    if (!config["root"].as_table()->contains("staging_area")) throw std::runtime_error("Missing 'staging_area' key in 'root' section.");
    if (!config["root"].as_table()->contains("logical_mount")) throw std::runtime_error("Missing 'logical_mount' key in 'root' section.");

    // DEVICES
    if (!config["devices"].is_array()) throw std::runtime_error("'devices' section must be an array.");
    toml::array *devices = config["devices"].as_array();
    for (const auto& device : *devices) {
        if (!device.is_table()) throw std::runtime_error("Each device in 'devices' section must be a table.");
        if (!device.as_table()->contains("name")) throw std::runtime_error("Missing 'name' key in a device in 'devices' section.");
        if (!device.as_table()->contains("physical_mount")) throw std::runtime_error("Missing 'physical_mount' key in a device in 'devices' section.");
    }

    return true;
}