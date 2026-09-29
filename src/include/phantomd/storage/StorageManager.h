#pragma once
#include <list>
#include <string>
#include "storage/Device.h"

class StorageManager {
    private:
        std::list<Device*> devices;
        
    public:
        StorageManager();
        ~StorageManager();
        
        bool mountDevice(const std::string& name);
        bool mountDevices();
        
        bool unmountDevice(const std::string& name);
        bool unmountDevices();
};