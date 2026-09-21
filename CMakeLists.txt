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

add_executable(Phantomd
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/daemonctl/daemonctl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rclonectl/rclonectl.cpp
)

target_include_directories(Phantomd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_link_libraries(Phantomd PRIVATE
    spdlog::spdlog
)

target_compile_options(Phantomd PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)