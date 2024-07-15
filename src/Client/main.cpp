#include <QApplication>
#include <QWindow>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QWindow window;
    window.show();

    return QApplication::exec();
}
