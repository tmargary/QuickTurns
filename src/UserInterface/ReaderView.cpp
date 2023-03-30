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
    std::string command = "python /home/tigran/Documents/_current/QuickTurns/src/UserInterface/Server.py " + std::to_string(port) + " " + path;
    std::system(command.c_str());
}

ReaderView::ReaderView(QWidget *parent) : QWidget(parent) {
    // Create the top part of the window
    QPushButton *leftButton = new QPushButton("Left");
    QPushButton *middleButton = new QPushButton("Middle");
    QPushButton *rightButton = new QPushButton("Right");
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(leftButton);
    topLayout->addWidget(new QFrame);
    topLayout->addWidget(middleButton);
    topLayout->addWidget(new QFrame);
    topLayout->addWidget(rightButton);
    
    // Create the middle part of the window
    QWebEngineProfile *profile = new QWebEngineProfile(this);
    QWebEnginePage *page = new QWebEnginePage(profile, this);
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

    // Create the bottom part of the window
    QPushButton *bottomLeftButton = new QPushButton("Left");
    QPushButton *bottomMiddleButton = new QPushButton("Middle");
    QPushButton *bottomRightButton = new QPushButton("Right");
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(bottomLeftButton);
    bottomLayout->addWidget(new QFrame);
    bottomLayout->addWidget(bottomMiddleButton);
    bottomLayout->addWidget(new QFrame);
    bottomLayout->addWidget(bottomRightButton);

    // Create the main layout and add the three parts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(webView, 1); // Set the web view to take up most of the space
    mainLayout->addLayout(bottomLayout);

    // Set the main layout for the window
    setLayout(mainLayout);

}

#include "moc_ReaderView.cpp"