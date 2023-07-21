#ifndef CESAMENETWORKMONITOR_H
#define CESAMENETWORKMONITOR_H

#include <string>

namespace Cesame
{

class NetworkMonitor
{
public:
    NetworkMonitor();

    void update();
    double sendPing(std::string address);

    double ping = -1;
    int lossCounter = 0;

private:
    std::string pingAddress = "192.168.1.1";
};

}

#endif // CESAMENETWORKMONITOR_H
