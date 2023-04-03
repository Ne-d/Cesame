#include "cesamelinegraph.h"
#include "cesamewindow.h"
#include "qpainter.h"
#include "utils.h"
#include <iostream>

CesameLineGraph::CesameLineGraph(CesameWindow* parent, double* inValue, CesameLineGraphSettings settings)
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&CesameLineGraph::updateData));

    value = inValue;
    textMargins = QMargins(10, 10, 10, 40);
    rectangleMargins = QMargins(textMargins.left(),
                                textMargins.top(),
                                textMargins.right(),
                                textMargins.bottom() + font.pointSize() * 3
                                );

    tableLength = settings.tableLength;

    maxValue = settings.maxValue;
    alarmValue = settings.alarmValue;
    criticalValue = settings.criticalValue;

    prefix = settings.prefix;
    postfix = settings.postfix;
}

void CesameLineGraph::paintEvent(QPaintEvent *event) {

    QPainter painter;
    painter.begin(this);

    rect = contentsRect().marginsRemoved(rectangleMargins);

    // Setting up QPen and QPainter parameters
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);
    painter.setFont(font);

    QColor lineColor = color;
    QColor prevLineColor;
    QColor borderColor = color;

    double ptHeight = 0;
    double nextPtHeight = 0;
    double xStep = rect.width() / tableLength;
    double heightMultiplier = rect.height() / maxValue;

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
        ptHeight = clamp_d(heightMultiplier * table.at(i), 0, rect.height());
        if(i < table.size() - 1) {
            nextPtHeight = clamp_d(heightMultiplier * table.at(i + 1), 0, rect.height());
        }
        else {
            nextPtHeight = clamp_d(heightMultiplier * table.at(i), 0, rect.height());
        }
        // TODO: Could probably be optimized by remembering the last point's position.
        // Using classes in this version could come in handy for that kind of stuff.

        // Draw line
        pen.setColor(prevLineColor); // Probably should be lineColor, idk why prevLineColor works better
        pen.setWidthF(LINE_WIDTH);
        painter.setPen(pen);
        painter.drawLine(QLineF(rect.x() + rect.width() - ((i) * xStep), rect.y() + rect.height() - ptHeight,
                                rect.x() + rect.width() - ((i + 1) * xStep), rect.y() + rect.height() - nextPtHeight));
    }

    // Draw Rectangle
    pen.setWidth(outlineWidth);
    pen.setColor(borderColor);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);
    painter.drawRect(rect);

    painter.drawText(contentsRect().marginsRemoved(textMargins).bottomLeft(), prefix + formatDouble(*value) + postfix);

    painter.end();
}

void CesameLineGraph::updateData()
{
    updateTable(*value);
    this->update();
}

void CesameLineGraph::updateTable(double value) {
    table.push_front(value);
    if(table.size() > tableLength) {
        table.pop_back();
    }
}
