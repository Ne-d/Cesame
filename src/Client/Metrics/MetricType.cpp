#include "MetricType.h"

using namespace Cesame;

MetricType::MetricType(const MetricName name, const unsigned int coreIndex,
                       const unsigned int monitorIndex):
    name(name),
    index(coreIndex),
    monitorIndex(monitorIndex) {}

MetricName MetricType::getName() const {
    return name;
}

unsigned int MetricType::getIndex() const {
    return index;
}

unsigned int MetricType::getMonitorIndex() const {
    return monitorIndex;
}

void MetricType::setName(const MetricName& name) {
    this->name = name;
}

void MetricType::setIndex(const unsigned int& index) {
    this->index = index;
}

void MetricType::setMonitorIndex(const unsigned int& monitorIndex) {
    this->monitorIndex = monitorIndex;
}
