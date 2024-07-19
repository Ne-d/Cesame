#include "TimeManager.h"

using namespace std::chrono;
using namespace Cesame;

TimeManager::TimeManager(const milliseconds interval) {
    timer.setInterval(interval);
    timer.setSingleShot(false);
    timer.start();
}

QTimer& TimeManager::getTimer() {
    return timer;
}

QMetaObject::Connection TimeManager::connect(const QObject* sender, const char* signal, const char* method,
                                             const Qt::ConnectionType type) const {
    return timer.connect(sender, signal, method, type);
}

void TimeManager::setInterval(const milliseconds interval) {
    timer.setInterval(interval);
}

time_point<steady_clock> TimeManager::getCurrentTimePoint() {
    return steady_clock::now();
}
