#include "ReaderView.h"
#include <QApplication>
#include <QQuickWindow>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QFileInfo>
#include <QSettings>
#include <thread>

void launchServer(int port, const std::string& path) {
    const std::string serverPath = "./UserInterface/Server.py";
    const std::string command = "python " + serverPath + " " + std::to_string(port) + " " + path;
    std::system(command.c_str());
}

ReaderView::ReaderView(QWidget *parent) : QWidget(parent), webView(new QWebEngineView(this)) {

    // Create the middle part of the window
    QWebEngineProfile *profile = new QWebEngineProfile(this);
    QWebEnginePage *page = new QWebEnginePage(profile, this);
    webView->setPage(page);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create the main layout and add the three parts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(webView, 1); // Set the web view to take up most of the space

    // Set the main layout for the window
    setLayout(mainLayout);
}


void ReaderView::loadFile(const QString &filePath)
{
    const QSettings settings;
    const QString serverPath = settings.value("folderPath").toString();
    
    const QFileInfo epubFileInfo(filePath);
    const int serverPort = 8081;

    const QString relativePath = filePath.mid(serverPath.length());

    std::thread serverThread(launchServer, serverPort, serverPath.toStdString());
    serverThread.detach();

    const QUrl bookPath = QUrl(QString("http://localhost:%1/%2").arg(serverPort).arg(relativePath));
    webView->setUrl(QUrl(QStringLiteral("qrc:/Styles/continuous-spreads.html?url=%1").arg(bookPath.toString())));
}

ReaderView::~ReaderView()
{
    delete webView->page();
}

#include "moc_ReaderView.cpp"
