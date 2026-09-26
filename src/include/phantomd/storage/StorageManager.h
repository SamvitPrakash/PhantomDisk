#pragma once
#include <list>
#include <string>

class StorageManager {
    private:
    public:
        StorageManager();
        ~StorageManager();
        
        bool mountDevice(const std::string& name);
        bool mountDevices();
        
        bool unmountDevice(const std::string& name);
        bool unmountDevices();
};