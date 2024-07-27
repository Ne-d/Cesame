#ifndef CPUCORESBARGRAPH_H
#define CPUCORESBARGRAPH_H

#include <qgridlayout.h>

#include "Bar.h"

namespace Cesame {
class CpuCoresBarGraph final : public QWidget {
public: // Methods
    CpuCoresBarGraph();

private: // Data
    QGridLayout layout;
    QList<Bar*> bars;
};
}

#endif //CPUCORESBARGRAPH_H
