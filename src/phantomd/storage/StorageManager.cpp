#include "storage/StorageManager.h"
#include "rclone_adapter/RcloneAdapter.h"
#include "types/DeviceState.h"

StorageManager::StorageManager(StorageConfig config) : CONFIG(config) {
    this->DEVICE_COUNT = 0;
    this->RCLONE_ADAPTER = new RcloneAdapter();

    for (const DeviceConfig& deviceConfig : CONFIG.DEVICES) {
        Device* device = new Device(deviceConfig.NAME, deviceConfig.MOUNT_POINT, this->RCLONE_ADAPTER);
        this->DEVICE.push_back(device);
        this->DEVICE_COUNT++;
    }
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
    return allMounted;
}

bool StorageManager::unmountDevices() {
    bool allUnmounted = true;
    for (Device* device : DEVICE) {
        if (!device->unmount()) {
            allUnmounted = false;
        }
    }
    return allUnmounted;
}

int StorageManager::healthCheck() const {
    int healthyCount = 0;
    for (const Device* device : DEVICE) {
        if (device->state() == DeviceState::MOUNTED) {
            healthyCount++;
        }
    }
    return healthyCount;
}