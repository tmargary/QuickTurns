#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

class HomeView : public QWidget {
    Q_OBJECT

public:
    explicit HomeView(QWidget *parent = nullptr);
    void saveButtonConfig(const QString &filePath);
    void loadButtonConfig();

private:
    QHBoxLayout *layout;
    QPushButton *button;
    QString configFilePath;
};