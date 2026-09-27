#include "rclone_adapter/RcloneAdapter.h"
#include <cstdlib>
#include <thread>
#include <chrono>

RcloneAdapter::RcloneAdapter() {}

bool RcloneAdapter::mount(const std::string& remote, const std::string& mountPoint){
    const std::string command = "rclone mount " + remote + " " + mountPoint;

    return std::system(command.c_str()) == 0;
}

bool RcloneAdapter::unmount(const std::string& mountPoint){
    const std::string command = "fusermount3 -u " + mountPoint;

    for(int i = 1; i <= RETRY_LIMIT; ++i) {
        if(std::system(command.c_str()) == 0) {
            return true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(this->INITIAL_WAIT_TIME * (i + 1)));

    }

    return std::system(command.c_str()) == 0;
}

bool RcloneAdapter::probe(const std::string& remote){
    const std::string command = "rclone lsd " + remote;

    const int result = std::system(command.c_str());

    return result == 0;
}