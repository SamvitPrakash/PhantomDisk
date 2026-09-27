#pragma once
#include <string>
#include "types/DeviceState.h"

class Device {
    private:
        std::string NAME;
        std::string MOUNTING_POINT;
        DeviceState STATE;

    public:
        Device(std::string name, std::string mount);
        ~Device();
        bool probe() const;
        bool state() const;
        bool mount();
        bool unmount();

};
