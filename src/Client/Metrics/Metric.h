#ifndef METRIC_H
#define METRIC_H

#include <variant>
#include <string>

namespace Cesame {
/**
 * A variant representing a metric (such as CPU temperature, disk usage, etc.).
 * It can either be a quantity (double or int) or a string.
 */
using Metric = std::variant<double, std::string>;

inline std::optional<double> metricToDouble(Metric metric) {
    if (std::holds_alternative<double>(metric))
        return std::optional{std::get<double>(metric)};

    return std::nullopt;
}
}

#endif //METRIC_H
