#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>

struct LogicalDriveConfig {
    std::unordered_map<std::string, std::filesystem::path> FRAMES;
    std::filesystem::path PAGE;
    
};