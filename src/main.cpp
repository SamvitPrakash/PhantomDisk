#include <iostream>
#include "daemonctl/daemonctl.h"
using namespace std;

int main() {
    cout << "Phantom Disk daemon starting...\n";

    DaemonCtl* daemonCtl = new DaemonCtl();
    daemonCtl->start();

    delete daemonCtl;
    daemonCtl = nullptr;

    return 0;
}