#include <QApplication>
#include <QFile>
#include <QTextBrowser>
#include <QTextDocument>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("/home/tigran/Downloads/abc/OEBPS/ch01.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }

    QTextBrowser browser;
    QTextDocument document;
    document.setHtml(file.readAll());
    browser.setDocument(&document);
    browser.show();

    QObject::connect(&browser, &QTextBrowser::anchorClicked, [&document]() {
        if (!document.isUndoRedoEnabled()) {
            document.setUndoRedoEnabled(true);
        }
        document.redo();
    });

    return app.exec();
}