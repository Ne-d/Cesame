#ifndef LABEL_H
#define LABEL_H

// Standard Library
#include <variant>

// Qt
#include <QWidget>

// Project files
#include "CesameWindow.h"
#include "MetricsManager.h"

namespace Cesame
{

typedef std::variant<MetricDefinition, QString> LabelTextCell;

class Label : public QWidget
{
    Q_OBJECT
public:
    explicit Label(CesameWindow *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    void updateDisplayString();
    QList<LabelTextCell> textList;

protected:
    QString displayString;

};

}

Cesame::Label &operator<<(Cesame::Label &label, Cesame::LabelTextCell cell);

#endif // LABEL_H
