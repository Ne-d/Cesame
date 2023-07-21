#include "qpainter.h"

#include "Utils.h"
#include "BarGraph.h"

using namespace Cesame;

BarGraph::BarGraph(CesameWindow *parent, double inValue, double inMaxValue, ColorList inColorList)
{
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&BarGraph::updateData));

    value = inValue;
    maxValue = inMaxValue;
    colorList = inColorList;

    setContentsMargins(margins);

    updateData();
}

BarGraph::BarGraph(QWidget *parent, double inMaxValue, ColorList inColorList)
{
    maxValue = inMaxValue;
    colorList = inColorList;

    setContentsMargins(margins);

    updateData();
}

void BarGraph::updateData()
{
    // TODO: Why the fuck does this even exist?
    this->update();
}

void BarGraph::paintEvent(QPaintEvent *event)
{
    // Initialisations
    QPainter painter;
    painter.begin(this);
    QPen pen;

    // Get color based on the current displayed value
    QColor currentColor = colorList.interpret(value);
    pen.setColor(currentColor);
    QBrush brush(currentColor);

    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);

    painter.drawRect(contentsRect());

    double height = (value / maxValue) * contentsRect().height();
    QRectF bar = QRectF(contentsRect().left(), contentsRect().bottom() - (height ), contentsRect().width(), height);

    painter.fillRect(bar, brush);

    painter.end();
}

void BarGraph::setValue(double inValue)
{
    value = inValue;
}
