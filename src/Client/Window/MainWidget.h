#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qwidget.h>

namespace Cesame {
class MainWidget final : public QWidget {
public:
    MainWidget();

private: // Demo setup methods
    void setupMainDemo();
    void setupLineGraphDemo();
};
}

#endif //MAINWIDGET_H
