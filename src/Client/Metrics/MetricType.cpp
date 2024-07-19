#include "MetricType.h"

using namespace Cesame;

MetricType::MetricType(const MetricName name, const unsigned int coreIndex,
                       const unsigned int monitorIndex):
    name(name),
    coreIndex(coreIndex),
    monitorIndex(monitorIndex) {}

MetricName MetricType::getName() const {
    return name;
}

unsigned int MetricType::getCoreIndex() const {
    return coreIndex;
}

unsigned int MetricType::getMonitorIndex() const {
    return monitorIndex;
}

void MetricType::setName(const MetricName& name) {
    this->name = name;
}

void MetricType::setCoreIndex(const unsigned int& coreIndex) {
    this->coreIndex = coreIndex;
}

void MetricType::setMonitorIndex(const unsigned int& monitorIndex) {
    this->monitorIndex = monitorIndex;
}
