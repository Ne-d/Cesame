#ifndef METRIC_H
#define METRIC_H

#include <variant>
#include <string>

namespace Cesame {
/**
 * A variant representing a metric (such as CPU temperature, disk usage, etc.).
 * It can either be a quantity (double or int) or a string.
 */
using Metric = std::variant<double, int, std::string>;
}

#endif //METRIC_H
