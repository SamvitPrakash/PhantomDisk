#include "rclone_adapter/RcloneAdapter.h"
#include <cstdlib>

RcloneAdapter::RcloneAdapter() {}

bool RcloneAdapter::mount(const std::string& remote, const std::string& mountPoint){
    const std::string command = "rclone mount " + remote + " " + mountPoint;

    return std::system(command.c_str()) == 0;
}

bool RcloneAdapter::unmount(const std::string& mountPoint){
    const std::string command = "fusermount3 -u " + mountPoint;

    return std::system(command.c_str()) == 0;
}

bool RcloneAdapter::probe(const std::string& remote){
    const std::string command = "rclone lsd " + remote;

    const int result = std::system(command.c_str());

    return result == 0;
}