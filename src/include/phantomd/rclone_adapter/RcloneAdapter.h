#pragma once

#include <string>

class RcloneAdapter{
    private:
        int RETRY_LIMIT = 6;
        int INITIAL_WAIT_TIME = 5000;

    public:
        RcloneAdapter();
        ~RcloneAdapter() = default;

        bool mount(const std::string& remote, const std::string& mountPoint);
        bool unmount(const std::string& mountPoint);
        bool probe(const std::string& remote);
};