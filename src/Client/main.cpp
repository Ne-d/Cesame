#include <QApplication>
#include <au.hh>
#include <iostream>
#include <thread>

#include "CpuMonitor.h"
#include "Monitor.h"

using namespace Cesame;
using namespace au;
using namespace au::symbols;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    //QWindow window;
    //window.show();

    CpuMonitor mon;

    while (true) {
        Metric<Percent, double> m = mon.usageRateAverage();

        Quantity<Percent, double> q;
        if (std::holds_alternative<Quantity<Percent, double>>(m))
            q = std::get<Quantity<Percent, double>>(m);

        std::cout << q << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return QApplication::exec();
}
