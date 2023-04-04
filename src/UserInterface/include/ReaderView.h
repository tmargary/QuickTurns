#pragma once

#include <QtWidgets>

class ReaderView : public QWidget {
    Q_OBJECT

public:
    explicit ReaderView(QWidget *parent = nullptr);
    virtual ~ReaderView() = default;
};