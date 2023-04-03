#ifndef CESAMELINEGRAPH_H
#define CESAMELINEGRAPH_H

#include <QWidget>
#include <deque>

#include "cesamewindow.h"
#include "utils.h"

struct CesameLineGraphSettings
{
    unsigned int tableLength = 300;

    double maxValue;
    double alarmValue;
    double criticalValue;

    QColor color = COLOR_WHITE;
    QColor alarmColor = COLOR_ORANGE;
    QColor criticalColor = COLOR_RED;

    QString prefix;
    QString postfix;
};

class CesameLineGraph : public QWidget
{
    Q_OBJECT

public:
    CesameLineGraph(CesameWindow* parent, double* inValue, CesameLineGraphSettings settings);

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
    QRectF rect;
    QMargins rectangleMargins;
    QMargins textMargins;
    double maxValue = 100;
    double lineWidth = 1.75;
    double outlineWidth = 1.75;

    // Alarms and colors
    QColor color = QColor(255, 255, 255, 255);
    double alarmValue = 65;
    QColor alarmColor = QColor(255, 192, 77, 255);
    double criticalValue = 75;
    QColor criticalColor = QColor(255, 77, 77, 255);

    // Text
    QString prefix = "";
    QString postfix = "";
    QFont font = QFont("Mono", 12);
};

#endif // CESAMELINEGRAPH_H
