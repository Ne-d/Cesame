#ifndef CESAMEWINDOW_H
#define CESAMEWINDOW_H

// Qt Includes
#include <QWidget>
#include "qtimer.h"

#include "Monitor.h"

class CesameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CesameWindow(QWidget *parent = nullptr);
    QTimer *timer;

    Cesame::Monitor *mon;

public slots:
    void update();
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    QWidget *background;
    int frameTime = 1000;
};

#endif // CESAMEWINDOW_H
