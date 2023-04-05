#pragma once
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

class HomeView : public QWidget {
    Q_OBJECT

public:
    explicit HomeView(QWidget *parent = nullptr);
    void setupListWidget();
    void setupAddFileButton();
    void saveButtonConfig(const QString &filePath);
    void loadButtonConfig();

private:
    QListWidget *listWidget;
    QVBoxLayout *layout;
    QString configFilePath;
};