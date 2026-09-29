#pragma once

#include <unistd.h>
enum class StorageState {
    MOUNTED,
    UNMOUNTED,
    DEGRADED,
    ERROR
};