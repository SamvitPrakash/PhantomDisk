#include "storage/Device.h"

Device::Device(std::string name, std::string mount) : NAME(name), MOUNTING_POINT(mount) {}

Device::~Device() {}

bool Device::probe() const {
    
    return true;
}