#ifndef METRICSMANAGER_H
#define METRICSMANAGER_H

#include "MonitorTypes.h"

#include <variant>
#include <vector>

#include <boost/interprocess/managed_shared_memory.hpp>

namespace Cesame {

typedef std::variant<int, double> Metric;

typedef struct {
    MetricEnum metric;
    MetricsUnit unit;
    unsigned int index;
} MetricDefinition;

MetricDefinition mDef(MetricEnum metric, MetricsUnit unit, unsigned int index);

class MetricsManager {
public: // Methods
    static void init();

    /**
     * @brief Get the current value of a metric from the server
     * @param name The name of the metric to get
     * @param unit The unit to convert the metric to
     * @return The desired metric
     */
    static Metric getMetric(MetricEnum name, Cesame::MetricsUnit unit = None, unsigned int index = 0);

private: // Methods
    template<typename T>
    static T shmGet(std::string name);

    static double unitMultiplier(MetricsUnit unit);

private: // Member variables
    static boost::interprocess::managed_shared_memory *shm;
    static std::string shmName;

private: // Exceptions
    class IncorrectMetricException : public std::exception {
        const char* what() const noexcept { return "Failed to retrieve metric."; }
    };

    class IncorrectUnitException : public std::exception {
        const char* what() const noexcept { return "Failed to convert to unit."; }
    };

    class ShmNotFoundException : public std::exception {
        const char* what() const noexcept { return "The requested metric was not found in the shared memory."; }
    };

};

} // Namespace Cesame(

#endif // METRICSMANAGER_H
