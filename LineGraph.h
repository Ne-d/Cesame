#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <deque>

#include <QWidget>
#include <QVBoxLayout>

#include "CesameWindow.h"
#include "Label.h"
#include "Color.h"

namespace Cesame
{

struct LineGraphSettings
{
    unsigned int tableLength = 300;

    double maxValue;
    double alarmValue;
    double criticalValue;

    QColor color = CESAME_COLOR_DEFAULT;
    QColor alarmColor = CESAME_COLOR_ORANGE;
    QColor criticalColor = CESAME_COLOR_RED;
};

class LineGraph : public QWidget
{
    Q_OBJECT

public:
    LineGraph(CesameWindow* parent, double* inValue, LineGraphSettings settings);

    void updateTable(double value);

public slots:
    void paintEvent(QPaintEvent *event);
    void updateData();

private:
    // Data
    double *value;
    std::deque<double> table;
    unsigned int tableLength = 100;

    // Dimensions
    double maxValue = 100;
    double lineWidth = 1.75;
    double outlineWidth = 1.75;

    // Alarms and colors
    QColor color = QColor(255, 255, 255, 255);
    double alarmValue = 65;
    QColor alarmColor = QColor(255, 192, 77, 255);
    double criticalValue = 75;
    QColor criticalColor = QColor(255, 77, 77, 255);
};

class LineGraphText : public QVBoxLayout
{
public:
    LineGraphText(CesameWindow* parent, double* inValue, LineGraphSettings lineGraphSettings);

    LineGraph* lineGraph;
    Label* label;
};

}

#endif // LINEGRAPH_H
