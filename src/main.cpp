#include <QApplication>
#include <QWidget>

#include "MainView/MainView.h"
#include "ReaderView/ReaderView.h"

int main(int argc, char *argv[])
{
    //
    QApplication app(argc, argv);
    MainView mainView;
    mainView.show();

    return QApplication::exec();
}