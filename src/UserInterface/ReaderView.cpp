#include "ReaderView.h"
#include <QApplication>
#include <QQuickWindow>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWidget>
#include <QMainWindow>

void launchServer(int port, const std::string& path) {
    std::string serverPath = "./UserInterface/Server.py";
    std::string command = "python " + serverPath + " " + std::to_string(port) + " " + path;
    std::system(command.c_str());
}


ReaderView::ReaderView(QWidget *parent) : QWidget(parent) {

    // Create the middle part of the window
    QWebEngineProfile *profile = new QWebEngineProfile();
    QWebEnginePage *page = new QWebEnginePage(profile, this);
    profile->setParent(page);
    QWebEngineView *webView = new QWebEngineView(this);
    webView->setPage(page);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QString epubFilePath = "/home/tigran/Documents/_current/QuickTurns/test/data/sample.epub";
    QFileInfo epubFileInfo(epubFilePath);
    QString serverPath = epubFileInfo.absolutePath();
    int serverPort = 8000;

    std::thread serverThread(launchServer, serverPort, serverPath.toStdString());
    serverThread.detach();

    QUrl bookPath = QUrl(QString("http://localhost:%1/%2").arg(serverPort).arg(epubFileInfo.fileName()));
    webView->setUrl(QUrl(QStringLiteral("qrc:/Styles/continuous-spreads.html?url=%1").arg(bookPath.toString())));

    // Create the main layout and add the three parts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(webView, 1); // Set the web view to take up most of the space

    // Set the main layout for the window
    setLayout(mainLayout);
}

#include "moc_ReaderView.cpp"
