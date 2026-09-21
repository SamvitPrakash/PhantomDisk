#include "rclonectl/rclonectl.h"

RcloneCtl::RcloneCtl() : rclonePid_(-1) {}

bool RcloneCtl::mount() {
    if (rclonePid_ != -1) {
        spdlog::error("rclone is already running");
        return false;
    }

    pid_t pid = fork();

    if (pid < 0) {
        spdlog::error("Failed to fork rclone process");
        return false;
    }

    if (pid == 0) {
        execl(
            "/usr/bin/rclone",
            "rclone",
            "mount",
            "OneDrive:",
            "/home/_c3rberus/Documents/Github/PhantomDisk/mnt",
            static_cast<char*>(nullptr)
        );

        // Only reached if execl() failed.
        spdlog::error("Failed to execute rclone");
        _exit(1);
    }

    rclonePid_ = pid;

    spdlog::info("Started rclone with PID: " + std::to_string(rclonePid_));

    return true;
}

bool RcloneCtl::unmount() {
    if (rclonePid_ == -1) {
        spdlog::error("rclone is not running");
        return false;
    }

    if (kill(rclonePid_, SIGTERM) != 0) {
        spdlog::error("Failed to terminate rclone");
        return false;
    }

    waitpid(rclonePid_, nullptr, 0);

    rclonePid_ = -1;

    spdlog::info("rclone stopped");

    return true;
}