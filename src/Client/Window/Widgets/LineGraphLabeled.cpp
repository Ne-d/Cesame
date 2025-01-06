#include "LineGraphLabeled.h"

#include <QSizePolicy>

namespace Cesame {
LineGraphLabeled::LineGraphLabeled(const QList<LineGraphElement>& lineGraphElements,
                                   const unsigned int nbDataPoints,
                                   const QList<LabelElement>& labelElements,
                                   const unsigned int colorRangeElementIndex) :
    lineGraph(this, lineGraphElements, nbDataPoints),
    label(this, labelElements, colorRangeElementIndex) {
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
