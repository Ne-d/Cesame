#ifndef CESAMELABEL_H
#define CESAMELABEL_H

#include <QWidget>
#include <cesamewindow.h>

class CesameLabel : public QWidget
{
    Q_OBJECT
public:
    explicit CesameLabel(CesameWindow *parent = nullptr);
    void updateData();

signals:

};

#endif // CESAMELABEL_H
