#include <QApplication>
#include <QWidget>

#include "QuickTurns.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QuickTurns qt;
    qt.show();
    return QApplication::exec();
}
