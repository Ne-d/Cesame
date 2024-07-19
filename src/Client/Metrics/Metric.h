#ifndef METRIC_H
#define METRIC_H

#include <au.hh>
#include <variant>
#include <string>

namespace Cesame {
/**
 * A variant representing a metric (such as CPU temperature, disk usage, etc.).
 * It can be either a Quantity or a string.
 *
 * @tparam Unit The unit of the metric, if it's a quantity.
 * @tparam Ref The underlying type representing the quantity (int, double, etc.).
 */
template <typename Unit, typename Ref>
using Metric = std::variant<au::Quantity<Unit, Ref>, au::QuantityPoint<Unit, Ref>, std::string>;
}

#endif //METRIC_H
