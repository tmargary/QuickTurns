
#include "Server.h"
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QByteArray>
#include <QTextStream>

HttpFileServer::HttpFileServer(QObject *parent) : QObject(parent) {
    connect(&tcpServer, &QTcpServer::newConnection, this, &HttpFileServer::onNewConnection);
}

bool HttpFileServer::start(quint16 port, const QString &rootPath) {
    this->rootPath = rootPath;
    return tcpServer.listen(QHostAddress::Any, port);
}

void HttpFileServer::onNewConnection() {
    QTcpSocket *socket = tcpServer.nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &HttpFileServer::onSocketReadyRead);
}

void HttpFileServer::onSocketReadyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) {
        return;
    }

    // Read the request
    QByteArray request = socket->readAll();
    QTextStream requestStream(request);

    QString method;
    QString path;
    QString httpVersion;

    requestStream >> method >> path >> httpVersion;

    QUrl url = QUrl::fromPercentEncoding(path.toUtf8());
    QString localPath = QDir::cleanPath(rootPath + url.path());

    if (localPath.endsWith('/') || QFileInfo(localPath).isDir()) {
        localPath += "/index.html";
    }

    QFile file(localPath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileContent = file.readAll();

        // Send the response header
        QByteArray responseHeader;
        QTextStream responseHeaderStream(&responseHeader);
        responseHeaderStream << "HTTP/1.1 200 OK\r\n";
        responseHeaderStream << "Content-Type: application/octet-stream\r\n";
        responseHeaderStream << "Content-Length: " << fileContent.size() << "\r\n";
        responseHeaderStream << "Access-Control-Allow-Origin: *\r\n";
        responseHeaderStream << "Connection: close\r\n";
        responseHeaderStream << "\r\n";

        socket->write(responseHeader + fileContent);
    } else {
        // Send a 404 response
        QByteArray responseHeader;
        QTextStream responseHeaderStream(&responseHeader);
        responseHeaderStream << "HTTP/1.1 404 Not Found\r\n";
        responseHeaderStream << "\r\n";

        socket->write(responseHeader + "404 Not Found");
    }

    // Close the socket when done
    connect(socket, &QTcpSocket::bytesWritten, [=](qint64 bytes) {
        if (bytes == socket->bytesToWrite()) {
            socket->close();
            socket->deleteLater();
        }
    });
}

#include "moc_Server.cpp"