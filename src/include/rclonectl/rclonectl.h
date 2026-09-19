#ifndef RCLONECTL_H
#define RCLONECTL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <spdlog/spdlog.h>

class RcloneCtl {
    public:
        RcloneCtl();

        bool mount();
        bool unmount();

    private:
        pid_t rclonePid_;
};

#endif