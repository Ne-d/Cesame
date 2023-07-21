#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <CesameWindow.h>
#include <variant>

namespace Cesame
{

typedef std::variant<double*, int*, QString> LabelTextCell;

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


signals:

};

}

Cesame::Label &operator<<(Cesame::Label &label, Cesame::LabelTextCell cell);

#endif // LABEL_H
