#ifndef METRIC_H
#define METRIC_H

#include <au.hh>
#include <variant>
#include <string>

namespace Cesame {
template <typename Unit, typename Ref>
using Metric = std::variant<au::Quantity<Unit, Ref>, std::string>;
}

#endif //METRIC_H
