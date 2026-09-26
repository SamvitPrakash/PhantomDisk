#include "Logger.h"
#include <stdexcept>
#include <vector>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger(const std::string& executable, const std::string& log_file, spdlog::level::level_enum log_level) {
    try {
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file, false);

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        std::vector<spdlog::sink_ptr> sinks{file_sink, console_sink};

        logger_ = std::make_shared<spdlog::logger>(executable, sinks.begin(), sinks.end());

        logger_->set_level(log_level);

        logger_->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [%n] %v");

        logger_->flush_on(spdlog::level::err);
    }
    catch (const spdlog::spdlog_ex& ex) {
        throw std::runtime_error("Failed to initialize logger: " + std::string(ex.what()));
    }
}

std::shared_ptr<spdlog::logger> Logger::get(const std::string& section) const {
    auto section_logger = std::make_shared<spdlog::logger>(logger_->name() + "." + section, logger_->sinks().begin(), logger_->sinks().end());

    section_logger->set_level(logger_->level());

    section_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [%n] %v");

    return section_logger;
}