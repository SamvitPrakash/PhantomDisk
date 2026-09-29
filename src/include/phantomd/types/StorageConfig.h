#pragma once
#include <string>
#include <filesystem>
#include <list>

struct DeviceConfig {
    std::string NAME;
    std::filesystem::path MOUNT_POINT;

};

struct StorageConfig {
    int RETRY_LIMIT;

    std::filesystem::path STAGING_AREA;
    std::list<DeviceConfig> DEVICES;
};