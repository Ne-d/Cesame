#include <QApplication>
#include <au.hh>
#include <iostream>
#include <thread>

#include "CpuMonitor.h"
#include "MemoryMonitor.h"
#include "Monitor.h"

using namespace Cesame;
using namespace au;
using namespace au::symbols;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    //QWindow window;
    //window.show();

    MemoryMonitor mon;

    while (true) {
        Metric<Gibi<Bytes>, double> m = mon.used();

        Quantity<Gibi<Bytes>, double> q;
        if (std::holds_alternative<Quantity<Gibi<Bytes>, double>>(m))
            q = std::get<Quantity<Gibi<Bytes>, double>>(m);

        std::cout << q << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return QApplication::exec();
}
