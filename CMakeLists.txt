cmake_minimum_required(VERSION 4.4)

project(PhantomDisk
    VERSION 1.0.0
    DESCRIPTION "Cloud Mounting Service"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib/spdlog)

add_executable(PhantomDiskd
    src/main.cpp
)

target_link_libraries(PhantomDiskd PRIVATE
    spdlog::spdlog
)

target_compile_options(PhantomDiskd PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)