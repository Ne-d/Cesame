#ifndef LINEGRAPH_H
#define LINEGRAPH_H

// Standard library
#include <deque>

// Qt
#include <QWidget>
#include <QVBoxLayout>

// Project files
#include "CesameWindow.h"
#include "MonitorTypes.h"
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
    LineGraph(CesameWindow* parent, MetricDefinition definition, LineGraphSettings settings);

    void updateTable(double value);

public slots:
    void paintEvent(QPaintEvent *event);
    void updateData();

private:
    MetricEnum metric;
    MetricsUnit unit;
    unsigned int metricIndex;

    // Data
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

private: // Exceptions
    class IncorrectMetricTypeException : public std::exception {
        const char* what() const noexcept {
            return "Failed to update values: the chosen metric returned an incorrect type "
                   "(cannot draw the graph for a string value for example).";
        }
    }; // Class IncorrectMetricTypeException

}; // Class LineGraph

class LineGraphText : public QWidget {
public:
    LineGraphText(CesameWindow* parent, MetricDefinition definition, LineGraphSettings settings);
    Label* label;

private:
    QVBoxLayout* layout;
    LineGraph* lineGraph;
};

}

#endif // LINEGRAPH_H
