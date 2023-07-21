#include "LineGraph.h"
#include "CesameWindow.h"
#include "qpainter.h"
#include "Utils.h"
#include <iostream>

using namespace Cesame;

LineGraph::LineGraph(CesameWindow* parent, double* inValue, LineGraphSettings settings)
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&LineGraph::updateData));

    value = inValue;

    tableLength = settings.tableLength;

    maxValue = settings.maxValue;
    alarmValue = settings.alarmValue;
    criticalValue = settings.criticalValue;
}

void LineGraph::paintEvent(QPaintEvent *event) {

    QPainter painter;
    painter.begin(this);

    // Setting up QPen and QPainter parameters
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);

    QColor lineColor = color;
    QColor prevLineColor;
    QColor borderColor = color;

    double ptHeight = 0;
    double nextPtHeight = 0;
    double xStep = contentsRect().width() / tableLength;
    double heightMultiplier = contentsRect().height() / maxValue;

    // Main drawing loop
    for(unsigned int i = 0; i < table.size(); i++) {
        prevLineColor = lineColor;

        // Calculate line color
        if(table.at(i) < alarmValue) {
            lineColor = color;
        }
        else if(table.at(i) >= alarmValue && table.at(i) < criticalValue) {
            lineColor = alarmColor;
        }
        else if(table.at(i) >= criticalValue) {
            lineColor = criticalColor;
        }

        // Determine outline color
        if(table.front() < alarmValue) {
            borderColor = color;
        }
        else if(table.front() >= alarmValue && table.front() < criticalValue) {
            borderColor = alarmColor;
        }
        else if(table.front() >= criticalValue) {
            borderColor = criticalColor;
        }

        // Caluclate point height
        ptHeight = clamp_d(heightMultiplier * table.at(i), 0, contentsRect().height());
        if(i < table.size() - 1) {
            nextPtHeight = clamp_d(heightMultiplier * table.at(i + 1), 0, contentsRect().height());
        }
        else {
            nextPtHeight = clamp_d(heightMultiplier * table.at(i), 0, contentsRect().height());
        }
        // TODO: Could probably be optimized by remembering the last point's position.
        // Using classes in this version could come in handy for that kind of stuff.

        // Draw line
        pen.setColor(prevLineColor); // Probably should be lineColor, idk why prevLineColor works better
        pen.setWidthF(LINE_WIDTH);
        painter.setPen(pen);
        // TODO: Why the fuck is this in a single line?
        painter.drawLine(QLineF(contentsRect().x() + contentsRect().width() - ((i) * xStep), contentsRect().y() + contentsRect().height() - ptHeight,
                                contentsRect().x() + contentsRect().width() - ((i + 1) * xStep), contentsRect().y() + contentsRect().height() - nextPtHeight));
    }

    // Draw Rectangle
    pen.setWidth(outlineWidth);
    pen.setColor(borderColor);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);
    painter.drawRect(contentsRect());

    painter.end();
}

void LineGraph::updateData()
{
    updateTable(*value);
    this->update();
}

void LineGraph::updateTable(double value) {
    table.push_front(value);
    if(table.size() > tableLength) {
        table.pop_back();
    }
}

LineGraphText::LineGraphText(CesameWindow *parent, double *inValue, LineGraphSettings lineGraphSettings)
{
    lineGraph = new LineGraph(parent, inValue, lineGraphSettings);
    label = new Label(parent);

    addWidget(lineGraph);
    addWidget(label);

    setSpacing(0);
}
