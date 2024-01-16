// Standard library
#include <iostream>

// Qt
#include <QPainter>

// Project files
#include "MetricsManager.h"
#include "Label.h"
#include "Utils.h"
#include "Color.h"


using namespace Cesame;

Label::Label(CesameWindow *parent)
    : QWidget{parent}
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&Label::updateDisplayString));

    updateDisplayString();
}

void Label::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QFont font = QFont("mono");
    font.setPixelSize(30);

    // TODO: Scawy magic numbew plz fix UwU
    setMaximumHeight(font.pixelSize() * 1.5);

    pen.setWidth(LINE_WIDTH);
    pen.setColor(CESAME_COLOR_DEFAULT);

    painter.setPen(pen);
    painter.setFont(font);

    painter.drawText(QPoint(contentsRect().left(), contentsRect().top() + font.pixelSize()), displayString);
}

// Update member str to contain all the values in textList. This allows for any amount of values to monitor, and any text.
void Label::updateDisplayString()
{
    displayString = "";

    for(int i = 0; i < textList.size(); i++)
    {
        LabelTextCell currentCell = textList.at(i);
        if(std::holds_alternative<MetricDefinition>(currentCell)) {
            MetricDefinition def = std::get<MetricDefinition>(currentCell);
            Metric metric = MetricsManager::getMetric(def.metric, def.unit, def.index);
            double value = -1;

            if(std::holds_alternative<double>(metric)) {
                value = std::get<double>(metric);
            }
            else if(std::holds_alternative<int>(metric)) {
                value = static_cast<double>(std::get<int>(metric));
            }

            displayString.append(formatDouble(value));
        }
        else if(std::holds_alternative<QString>(currentCell))
        {
            displayString.append(std::get<QString>(currentCell));
        }
    }

    update(); // This updates the widget, managed by Qt.
}

Label &operator<<(Label &label, LabelTextCell cell)
{
    label.textList.append(cell);

    return label;
}
