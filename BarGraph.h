#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <QWidget>

#include "CesameWindow.h"
#include "Color.h"

namespace Cesame
{

struct BarGraphSettings
{
    double maxValue;
    double alarmValue;
    double criticalValue;

    QColor color = CESAME_COLOR_DEFAULT;
    QColor alarmColor = CESAME_COLOR_ORANGE;
    QColor criticalColor = CESAME_COLOR_RED;
};

class BarGraph : public QWidget
{
    Q_OBJECT
public:
    BarGraph(QWidget *parent, double inMaxValue, Cesame::ColorList inColorList);
    BarGraph(CesameWindow *parent, double inValue, double inMaxValue, Cesame::ColorList inColorList);

public slots:
    void updateData();
    void paintEvent(QPaintEvent *event);

private:
    double value;

    double maxValue;
    Cesame::ColorList colorList;

    QMargins margins = QMargins(0, 0, 0, 0);

public:
    void setValue(double inValue);
};

}

#endif // BARGRAPH_H
