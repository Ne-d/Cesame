#include <QApplication>
#include <QWindow>
#include <au.hh>
#include <iostream>
#include <thread>

#include "CpuMonitor.h"
#include "MetricType.h"
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
        Metric<Celsius, double> m = mon.temperaturePackage();
        QuantityPoint<Celsius, double> v;
        if (std::holds_alternative<QuantityPoint<Celsius, double>>(m))
            v = std::get<QuantityPoint<Celsius, double>>(m);

        std::cout << v << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return QApplication::exec();
}
