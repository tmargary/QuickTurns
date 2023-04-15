// #include <QtCore>
// #include <QtHttpServer>
// #include <fstream>
// #include <iostream>
// #include <string>

// static inline QString host(const QHttpServerRequest &request)
// {
//     return QString::fromLatin1(request.value("Host"));
// }
// class myServer{
// public:
//     myServer(){
//         //std::cout<<path<<std::endl;
//         httpServer.route("/", []() {
//         return "Hello world";
//     });
//     //   httpServer.route(path, [](const QHttpServerRequest &request) {
//     //      return "Hello from path world";
//     //  });

 
//     httpServer.route("/assets/<arg>", [] (const QUrl &url) {
//         return QHttpServerResponse::fromFile(QStringLiteral(":/assets/%1").arg(url.path()));
//     });

//     httpServer.route("/remote_address", [](const QHttpServerRequest &request) {
//         return request.remoteAddress().toString();
//     });

//     // Basic authentication example (RFC 7617)
//     httpServer.route("/auth", [](const QHttpServerRequest &request) {
//         auto auth = request.value("authorization").simplified();

//         if (auth.size() > 6 && auth.first(6).toLower() == "basic ") {
//             auto token = auth.sliced(6);
//             auto userPass = QByteArray::fromBase64(token);

//             if (auto colon = userPass.indexOf(':'); colon > 0) {
//                 auto userId = userPass.first(colon);
//                 auto password = userPass.sliced(colon + 1);

//                 if (userId == "Aladdin" && password == "open sesame")
//                     return QHttpServerResponse("text/plain", "Success\n");
//             }
//         }
//         QHttpServerResponse response("text/plain", "Authentication required\n",
//                                      QHttpServerResponse::StatusCode::Unauthorized);
//         response.setHeader("WWW-Authenticate", R"(Basic realm="Simple example", charset="UTF-8")");
//         return response;
//     });

//     httpServer.afterRequest([](QHttpServerResponse &&resp) {
//         resp.setHeader("Server", "Qt HTTP Server");
//         return std::move(resp);
//     });

//     const auto port = httpServer.listen(QHostAddress::Any);
//     if (!port) {
//         qDebug() << QCoreApplication::translate("QHttpServerExample",
//                                                 "Server failed to listen on a port.");
//        // return 0;
//     }

//     qDebug() << QCoreApplication::translate("QHttpServerExample",
//                                             "Running on http://127.0.0.1:%1/"
//                                             "(Press CTRL+C to quit)").arg(port);
//     }

// private:
//      QHttpServer httpServer;
//      //QString _path;

// };

// int main(int argc, char *argv[])
// {
//     QCoreApplication app(argc, argv);

//     myServer srever;
//     return app.exec();
// }

#include <QtCore>
#include <QtHttpServer>


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QHttpServer httpServer;
    // httpServer.setRootDir("C:/Users");
    httpServer.route("/", []() {
        return "Hello world";
    });


    const auto port = httpServer.listen(QHostAddress::LocalHost, 8000);

    qDebug() << QCoreApplication::translate("QHttpServerExample",
                                            "Running on http://127.0.0.1:%1/"
                                            "(Press CTRL+C to quit)").arg(port);
    return app.exec();
}
