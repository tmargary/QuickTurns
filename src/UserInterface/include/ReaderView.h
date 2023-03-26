#pragma once

#include <QtWidgets>
#include "Server.h"

class ReaderView : public QWidget {
    Q_OBJECT

public:
    explicit ReaderView(QWidget *parent = nullptr);
    virtual ~ReaderView() = default;

private:
    HttpFileServer *httpServer;
};