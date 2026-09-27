#include "storage/Device.h"
#include "types/DeviceState.h"

Device::Device(std::string name, std::string mount) : NAME(name), MOUNTING_POINT(mount) {
    STATE = DeviceState::OFFLINE;
}

Device::Device(std::string name, std::string mount, RcloneAdapter *adapter) : NAME(name), MOUNTING_POINT(mount), ADAPTER(adapter) {}

Device::~Device() {}

bool Device::probe() {
    if(ADAPTER) {
        if(ADAPTER->probe(NAME)) STATE = DeviceState::UNMOUNTED;
        else STATE = DeviceState::OFFLINE;
    }

    return STATE == DeviceState::UNMOUNTED;
}

DeviceState Device::state() const {
    return STATE;
}

bool Device::mount() {
    if(ADAPTER) {
        this->MOUNTING_THREAD = std::thread([this]() {
            if(ADAPTER->mount(NAME, MOUNTING_POINT)) STATE = DeviceState::MOUNTED;
            else STATE = DeviceState::ERROR;
            
            return STATE == DeviceState::MOUNTED;
        });
    }else{
        STATE = DeviceState::ERROR;
        return STATE == DeviceState::MOUNTED;
    }

    return true;
    
}

bool Device::unmount() {
    if(ADAPTER) {
        if(ADAPTER->unmount(MOUNTING_POINT)) STATE = DeviceState::UNMOUNTED;
        else STATE = DeviceState::ERROR;

        if(MOUNTING_THREAD.joinable()) {
            MOUNTING_THREAD.join();
        }
    }

    return STATE == DeviceState::UNMOUNTED;
}
