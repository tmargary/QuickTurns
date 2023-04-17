#pragma once
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

#include "DataBase.h"

class HomeView : public QWidget {
    Q_OBJECT

public:
    explicit HomeView(const QString &folderPath, QWidget *parent = nullptr);
    void setupListWidget();
    void setupAddFileButton();
    int saveButtonConfig(const std::string &filePath);
    void addBookToListWidget(const QString &bookName, const QString &bookPath);

signals:
    void itemClicked(const QString &filePath);

private:
    QListWidget *listWidget;
    QVBoxLayout *layout;
    QString configFilePath;
    BookDB database;
};