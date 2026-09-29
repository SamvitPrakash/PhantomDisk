#include "storage/StorageManager.h"
#include "rclone_adapter/RcloneAdapter.h"
#include "types/DeviceState.h"
#include <cstddef>

StorageManager::StorageManager(StorageConfig config) : CONFIG(config) {
    this->DEVICE_COUNT = 0;
    this->RCLONE_ADAPTER = new RcloneAdapter();
    this->STATE = StorageState::OFFLINE;

    for (const DeviceConfig& deviceConfig : CONFIG.DEVICES) {
        Device* device = new Device(deviceConfig.NAME, deviceConfig.MOUNT_POINT, this->RCLONE_ADAPTER);
        this->DEVICE.push_back(device);
        this->DEVICE_COUNT++;
    }

    this->STATE = StorageState::UNMOUNTED;
}

StorageManager::~StorageManager() {
    for (Device* device : DEVICE) {
        delete device;
    }

    this->DEVICE.clear();

    if(this->RCLONE_ADAPTER) {
        delete this->RCLONE_ADAPTER;
    }
}

bool StorageManager::mountDevice(const std::string& name) {
    for (Device* device : DEVICE) {
        if (device->name() == name) {
            return device->mount();
        }
    }
    return false; 

}

bool StorageManager::unmountDevice(const std::string& name) {
    for (Device* device : DEVICE) {
        if (device->name() == name) {
            return device->unmount();
        }
    }
    return false; 
}

bool StorageManager::mountDevices() {
    bool allMounted = true;
    for (Device* device : DEVICE) {
        if (!device->mount()) {
            allMounted = false;
        }
    }

    this->STATE = allMounted ? StorageState::MOUNTED : StorageState::DEGRADED;

    return allMounted;
}

bool StorageManager::unmountDevices() {
    bool allUnmounted = true;
    for (Device* device : DEVICE) {
        if (!device->unmount()) {
            allUnmounted = false;
        }
    }

    this->STATE = allUnmounted ? StorageState::UNMOUNTED : StorageState::DEGRADED;

    return allUnmounted;
}

double StorageManager::healthCheck() {
    size_t healthyCount = 0;
    for (const Device* device : DEVICE) {
        if (device->state() == DeviceState::MOUNTED) {
            healthyCount++;
        }
    }

    if(healthyCount == DEVICE.size()) this->STATE = StorageState::MOUNTED;
    else this->STATE = StorageState::DEGRADED;

    return static_cast<double>(healthyCount) / DEVICE.size() * 100;

}