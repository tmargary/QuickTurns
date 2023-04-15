#include <QApplication>
#include <QWidget>

#include "StackedView.h"


int main(int argc, char *argv[]) {
    const QApplication app(argc, argv);

    {
        StackedView stackedView;
        stackedView.show();
        return app.exec();
    }
}
