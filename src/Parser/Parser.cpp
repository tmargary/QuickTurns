#include <QApplication>
#include <QTextBrowser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextBrowser browser;
    browser.setHtml("<html><body><h1>Hello, World!</h1></body></html>");
    browser.show();

    return app.exec();
}