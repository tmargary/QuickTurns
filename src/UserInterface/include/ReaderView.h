#pragma once

#include <QWidget>

class QWebEngineView;

class ReaderView : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderView(QWidget *parent = nullptr);
    void loadFile(const QString &filePath);
    ~ReaderView();

private:
    QWebEngineView *webView;
};