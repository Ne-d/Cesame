#include <QApplication>
#include <au.hh>
#include <iostream>
#include <thread>

#include "GpuMonitor.h"
#include "Monitor.h"

using namespace Cesame;
using namespace au;
using namespace au::symbols;

template <typename Unit, typename Rep>
void printMetric(Metric<Unit, Rep> metric) {
    if (std::holds_alternative<Quantity<Unit, Rep>>(metric))
        std::cout << std::get<Quantity<Unit, Rep>>(metric);

    if (std::holds_alternative<QuantityPoint<Unit, Rep>>(metric))
        std::cout << std::get<QuantityPoint<Unit, Rep>>(metric);

    if (std::holds_alternative<std::string>(metric))
        std::cout << std::get<std::string>(metric);

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    //QWindow window;
    //window.show();

    GpuMonitor mon(0);

    while (true) {
        const Metric<Percent, int> m = mon.pState();

        printMetric(m);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return QApplication::exec();
}
