#include "LineGraphLabeled.h"

#include <QSizePolicy>

namespace Cesame {
LineGraphLabeled::LineGraphLabeled(const QList<LineGraphElement>& lineGraphElements,
                                   const unsigned int nbDataPoints,
                                   const QList<LabelElement>& labelElements) :
    lineGraph(this, lineGraphElements, nbDataPoints),
    label(this, labelElements) {
    // Set size policies
    constexpr QSizePolicy lineGraphSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lineGraph.setSizePolicy(lineGraphSizePolicy);

    constexpr QSizePolicy labelSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    label.setSizePolicy(labelSizePolicy);

    layout.addWidget(&lineGraph);
    layout.addWidget(&label);
    setLayout(&layout);
}
}
