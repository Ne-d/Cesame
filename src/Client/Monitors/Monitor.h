#ifndef MONITOR_H
#define MONITOR_H

#include "Metric.h"
#include "MetricType.h"
#include "Exceptions.h"

namespace Cesame {
class Monitor {
public:
    template <typename Unit, typename Rep>
    static Metric<Unit, Rep> getMetric(const MetricType& type) {
        switch (type.getName()) {
            default:
                throw NotImplementedException();
        }
    }

    /**
     * Moves the file stream's cursor to the beginning of the desired line.
     *
     * @param stream The stream to set to the desried line.
     * @param lineNb The number of the line to set the stream to, starting at 0.
     */
    static void goToLine(std::ifstream& stream, const unsigned int lineNb) {
        stream.seekg(0, std::ifstream::beg);
        for (int i = 0; i < lineNb; ++i) {
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};
}

#endif //MONITOR_H
