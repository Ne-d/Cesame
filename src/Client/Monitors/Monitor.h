#ifndef MONITOR_H
#define MONITOR_H

#include "Metric.h"
#include "MetricType.h"
#include "Exceptions/NotImplementedException.h"

namespace Cesame {
class Monitor {
public:
    template <typename Unit, typename Rep>
    static Metric<Unit, Rep> getMetric(const MetricType& type) {
        switch (type.getName()) {
            default:
                throw new NotImplementedException;
        }
    }
};
}

#endif //MONITOR_H
