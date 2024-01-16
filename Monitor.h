#ifndef MONITOR_H
#define MONITOR_H

#include <variant>

#include <QString>

#include "MonitorTypes.h"

namespace Cesame
{

typedef std::variant<double, QString, int> MonitorData;

class Monitor
{
public:
    Monitor();
    
    //MonitorData get(Metrics value, MetricsUnit unit, int valueIndex, int monitorIndex = 0);
};

}

#endif // MONITOR_H
