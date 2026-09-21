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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/phantomd/phantomd.cpp
)

add_executable(Phantom
    ${CMAKE_CURRENT_SOURCE_DIR}/src/phantom/phantom.cpp
)

add_executable(PhantomHaunt
    ${CMAKE_CURRENT_SOURCE_DIR}/src/phantom_haunt/phantomHaunt.cpp
)

target_include_directories(Phantomd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/phantomd
)
target_include_directories(Phantom PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/phantom
)

target_include_directories(PhantomHaunt PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/phantom_haunt
)

target_link_libraries(Phantomd PRIVATE
    spdlog::spdlog
)

target_link_libraries(Phantom PRIVATE
    spdlog::spdlog
)

target_link_libraries(PhantomHaunt PRIVATE
    spdlog::spdlog
)

target_compile_options(Phantomd PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_compile_options(Phantom PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_compile_options(PhantomHaunt PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)