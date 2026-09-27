#pragma once
#include <string>
#include <thread>
#include "types/DeviceState.h"
#include "rclone_adapter/RcloneAdapter.h"

class Device {
    private:
        std::string NAME;
        std::string MOUNTING_POINT;
        std::thread MOUNTING_THREAD;
        DeviceState STATE;
        RcloneAdapter *ADAPTER;

    public:
        Device(std::string name, std::string mount);
        Device(std::string name, std::string mount, RcloneAdapter *adapter);
        ~Device();
        DeviceState state() const;
        bool probe();
        bool mount();
        bool unmount();

};
