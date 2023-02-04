#include "cesamecpucoregraph.h"
#include "qpainter.h"

CesameCpuCoreGraph::CesameCpuCoreGraph(CesameWindow *parent): QWidget{parent}
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&CesameCpuCoreGraph::updateData));

    cpuMon = parent->cpuMon;

    margins = QMargins(10, 10, 10, 10);
    color = COLOR_WHITE;
    lines = 1;

    width = contentsRect().marginsRemoved(margins).width() / (cpuMon->coreCount / lines);
}

void CesameCpuCoreGraph::updateData()
{

}

void CesameCpuCoreGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Setting up QPen and QPainter parameters
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);

    painter.setPen(pen);

    for (unsigned int i = 0; i < cpuMon->coreCount; i++)
    {
        painter.drawRect(QRectF(contentsRect().left(), contentsRect().top(), width, 100));
    }

    // Draw Rectangle
    painter.setPen(pen);
    painter.drawRect(contentsRect().marginsRemoved(margins));
}
