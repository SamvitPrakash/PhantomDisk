#pragma once
#include <list>
#include <string>
#include "storage/Device.h"
#include "rclone_adapter/RcloneAdapter.h"
#include "types/StorageConfig.h"
#include "types/StorageState.h"

class StorageManager {
    private:
        int DEVICE_COUNT;
        std::list<Device*> DEVICE;
        RcloneAdapter *RCLONE_ADAPTER;
        StorageConfig CONFIG;
        StorageState STATE;
        
    public:
        StorageManager(StorageConfig config);
        ~StorageManager();
        
        bool mountDevice(const std::string& name);
        bool mountDevices();
        
        bool unmountDevice(const std::string& name);
        bool unmountDevices();

        double healthCheck();
};