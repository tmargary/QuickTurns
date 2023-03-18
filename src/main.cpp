/* #include <iostream>
#include "Parser/Parser.h"

int main() {
    EpubReader reader;
    
    if (reader.epub_init("/home/tigran/Shared/Professional C++ by Marc Gregoire.epub") == 0) {
        std::cerr << "Failed to open the EPUB file." << std::endl;
        return 1;
    }
    
    char* root_file = reader.get_root_file();
    if (root_file == nullptr) {
        std::cerr << "Failed to get the root file." << std::endl;
        reader.epub_destroy();
        return 1;
    }

    std::cout << "Root file: " << root_file << std::endl;
    
    reader.epub_destroy();
    return 0;
} */



/* #include <QApplication>
#include <QWidget>

#include "MainView/MainView.h"
#include "ReaderView/ReaderView.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainView mainView;
    mainView.show();

    return QApplication::exec();
} */


/* #include <QApplication>
#include <QFile>
#include <QWebEngineView>
#include <QWebEnginePage>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("/home/tigran/Downloads/abc/OEBPS/ch01.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }

    QWebEngineView view;
    QWebEnginePage page;
    view.setPage(&page);
    page.setHtml(file.readAll());
    view.show();

    return app.exec();
} */

int main(){return 0;}