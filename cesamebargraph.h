#ifndef CESAMEBARGRAPH_H
#define CESAMEBARGRAPH_H

#include <QWidget>

#include "cesamewindow.h"
#include "utils.h"

struct CesameBarGraphSettings
{
    double maxValue;
    double alarmValue;
    double criticalValue;

    QColor color = COLOR_WHITE;
    QColor alarmColor = COLOR_ORANGE;
    QColor criticalColor = COLOR_RED;
};

class CesameBarGraph : public QWidget
{
    Q_OBJECT
public:
    CesameBarGraph(QWidget *parent, CesameBarGraphSettings settings);
    CesameBarGraph(CesameWindow *parent, double inValue, CesameBarGraphSettings settings);

public slots:
    void updateData();
    void paintEvent(QPaintEvent *event);

private:
    double value;

    double maxValue;
    double alarmValue;
    double criticalValue;

    QMargins margins = QMargins(1, 1, 1, 1);

public:
    void setValue(double inValue);
};

#endif // CESAMEBARGRAPH_H
