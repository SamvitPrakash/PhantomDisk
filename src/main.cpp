#include "daemonctl/daemonctl.h"
#include <spdlog/spdlog.h>
#include <unistd.h>

using namespace std;

int main() {

    DaemonCtl* daemonCtl = new DaemonCtl();
    daemonCtl->start();

    delete daemonCtl;
    daemonCtl = nullptr;

    return 0;
}