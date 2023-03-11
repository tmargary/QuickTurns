#include <QApplication>
#include <QWidget>

#include "QuickTurns.h"

int main(int argc, char *argv[])
{
    //
    QApplication app(argc, argv);
    QuickTurns mainView;
    mainView.show();
    return QApplication::exec();
}
