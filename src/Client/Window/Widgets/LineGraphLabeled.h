#ifndef LINEGRAPHLABELED_H
#define LINEGRAPHLABELED_H
#include <qboxlayout.h>

#include "Label.h"
#include "LineGraph.h"
#include "MainWidget.h"

namespace Cesame {
class LineGraphLabeled final : public QWidget {
public: // Methods
    LineGraphLabeled(const QList<LineGraphElement>& lineGraphElements, unsigned int nbDataPoints,
                     const QList<LabelElement>& labelElements, unsigned int colorRangeElementIndex = 0);

private: // Data
    QVBoxLayout layout;
    LineGraph lineGraph;
    Label label;
};
}

#endif //LINEGRAPHLABELED_H
