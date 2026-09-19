#ifndef DAEMONCTL_H
#define DAEMONCTL_H

#include <atomic>
using namespace std;

class DaemonCtl {
    private:
        atomic<bool> shutdownRequested_;
        atomic<bool> restartRequested_;

    public:
        DaemonCtl();
        ~DaemonCtl();

        void start();
        void stop();
        void restart();
};

#endif