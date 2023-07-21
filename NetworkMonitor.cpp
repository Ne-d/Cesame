#include <iostream>
#include <format>

#include "NetworkMonitor.h"
#include "Utils.h"

using namespace Cesame;

NetworkMonitor::NetworkMonitor()
{
    update();
}

double NetworkMonitor::sendPing(std::string address)
{
    std::setlocale(LC_ALL, "C");
    double newPing;
    try {
        newPing = std::stod(exec("ping -c 1 192.168.1.1 | grep -E -o \"time=.+\" | grep -E -o \"[[:digit:]]+\.[[:digit:]]+\""));
    } catch (...) {
        newPing = 9999;
        lossCounter++;
    }

    return newPing;
}

void NetworkMonitor::update()
{
    ping = sendPing(pingAddress);
}
