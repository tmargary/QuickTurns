#pragma once

#include <QObject>
#include <QtNetwork/QTcpServer> // Change this line
#include <QtNetwork/QTcpSocket> // Change this line
#include <QFileInfo>


class HttpFileServer : public QObject {
    Q_OBJECT

public:
    explicit HttpFileServer(QObject *parent = nullptr);
    bool start(quint16 port, const QString &rootPath);

private slots:
    void onNewConnection();
    void onSocketReadyRead();

private:
    QTcpServer tcpServer;
    QString rootPath;
};


