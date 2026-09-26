#pragma once

#include <string>

class RcloneAdapter{
    public:
        RcloneAdapter() = default;
        ~RcloneAdapter() = default;

        bool mount(const std::string& remote, const std::string& mountPoint);
        bool unmount(const std::string& mountPoint);
};