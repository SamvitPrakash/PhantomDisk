#include <iostream>
#include <string>
#include "configurationctl/Configurationctl.h"

using namespace std;

int main(){
    Configurationctl config("/home/_c3rberus/Documents/Github/PhantomDisk/config/test.toml");
    config.load();
    cout << config.devices<string>(0, "physical_mount") << endl;

    return 0;
}