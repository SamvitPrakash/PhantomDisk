#pragma once
#include <memory>
#include <string>
#include <spdlog/logger.h>
#include <spdlog/common.h>

class Logger {
public:
    Logger(
        const std::string& executable,
        const std::string& log_file,
        spdlog::level::level_enum log_level
    );

    std::shared_ptr<spdlog::logger> get(
        const std::string& section
    ) const;

private:
    std::shared_ptr<spdlog::logger> logger_;
};