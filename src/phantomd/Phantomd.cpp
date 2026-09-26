#include <iostream>
#include "Logger.h"
#include "spdlog/common.h"

using namespace std;

int main(){
    try {
        Logger logger(
            "Phantomd",
            "/home/_c3rberus/Documents/Github/PhantomDisk/logs/phantomdisk-test.log",
            spdlog::level::info
        );

        auto log = logger.get("LoggerTest");

        log->trace("This is a TRACE message");
        log->debug("This is a DEBUG message");
        log->info("This is an INFO message");
        log->warn("This is a WARNING message");
        log->error("This is an ERROR message");
        log->critical("This is a CRITICAL message");

        log->info("Testing formatting: number={}, text={}", 42, "hello");

        std::cout << "Logger test completed.\n";
        std::cout << "Log file: /tmp/phantomdisk-test.log\n";

        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Logger test failed: "
                  << ex.what()
                  << '\n';

        return 1;
    }
}