#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>

namespace Cesame {
/**
 * A wrapper for a QTimer.
 * All widgets that need to update at once can connect to the same instance of this.
 */
class TimeManager {
private: // Fields
    QTimer timer;

public: //Methods
    explicit TimeManager(std::chrono::milliseconds interval);

    QTimer& getTimer();

    /**
     * Wrapper for the connect method of the timer.
     */
    QMetaObject::Connection connect(const QObject* sender,
                                    const char* signal, const char* method,
                                    Qt::ConnectionType type = Qt::AutoConnection) const;

    void setInterval(std::chrono::milliseconds interval);

    void start();

    static std::chrono::time_point<std::chrono::steady_clock> getCurrentTimePoint();
};

static TimeManager globalTimeManager(std::chrono::milliseconds(1000));
}

#endif //TIMEMANAGER_H
