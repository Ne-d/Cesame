#include "LineGraphLabeled.h"

#include <QSizePolicy>

namespace Cesame {
LineGraphLabeled::LineGraphLabeled(const QList<LineGraphElement>& lineGraphElements,
                                   const unsigned int nbDataPoints,
                                   const QList<LabelElement>& labelElements,
                                   const ColorRangeList& labelColorRanges,
                                   const unsigned int labelColorRangeElementIndex) :
    lineGraph(this, lineGraphElements, nbDataPoints),
    label(this, labelElements, labelColorRanges, labelColorRangeElementIndex) {
    // Set size policies
    constexpr QSizePolicy lineGraphSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lineGraph.setSizePolicy(lineGraphSizePolicy);

    constexpr QSizePolicy labelSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    label.setSizePolicy(labelSizePolicy);

    layout.addWidget(&lineGraph);
    layout.addWidget(&label);
    setLayout(&layout);
}
}
