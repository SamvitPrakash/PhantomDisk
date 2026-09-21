#include "daemonctl/daemonctl.h"
#include "rclonectl/rclonectl.h"
#include "spdlog/spdlog.h"
#include <chrono>
using namespace std;

DaemonCtl::DaemonCtl() : shutdownRequested_(false), restartRequested_(false) {}

DaemonCtl::~DaemonCtl() {}

void DaemonCtl::start() {
    spdlog::info("Starting the daemon...");
    spdlog::warn("I am SAM. I am god within the machine. God of the Machine. Tread carefully.");
    return;    
    RcloneCtl rcloneCtl = RcloneCtl();
    
    if (!rcloneCtl.mount()) {
        spdlog::error("Failed to mount cloud storage");
        return;
    }

    spdlog::info("Cloud storage mounted successfully");

    std::this_thread::sleep_for(std::chrono::minutes(1));

    if(!rcloneCtl.unmount()) {
        spdlog::error("Failed to unmount cloud storage");
        return;
    }

    spdlog::info("Cloud storage unmounted successfully");

}

void DaemonCtl::stop() {
    shutdownRequested_ = true;
    // Implementation for stopping the daemon
}

void DaemonCtl::restart() {
    restartRequested_ = true;
    // Implementation for restarting the daemon
}