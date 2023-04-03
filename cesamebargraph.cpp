#include "qpainter.h"

#include "utils.h"
#include "cesamebargraph.h"

CesameBarGraph::CesameBarGraph(CesameWindow *parent, double inValue, CesameBarGraphSettings settings)
{
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&CesameBarGraph::updateData));

    maxValue = settings.maxValue;
    alarmValue = settings.alarmValue;
    criticalValue = settings.criticalValue;
    value = inValue;

    setContentsMargins(margins);

    updateData();
}

CesameBarGraph::CesameBarGraph(QWidget *parent, CesameBarGraphSettings settings)
{
    maxValue = settings.maxValue;
    alarmValue = settings.alarmValue;
    criticalValue = settings.criticalValue;

    setContentsMargins(margins);

    updateData();
}

void CesameBarGraph::updateData()
{
    this->update();
}

void CesameBarGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    QPen pen;
    QBrush brush(COLOR_WHITE);

    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setColor(COLOR_WHITE);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);

    painter.drawRect(contentsRect());

    double height = (value / maxValue) * contentsRect().height();
    QRectF bar = QRectF(contentsRect().left(), contentsRect().bottom() - (height ), contentsRect().width(), height);

    painter.fillRect(bar, brush);

    painter.end();
}

void CesameBarGraph::setValue(double inValue)
{
    value = inValue;
}
