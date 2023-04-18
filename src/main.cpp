#include <QApplication>
#include <QFileDialog>
#include <QSettings>
#include <QPushButton>
#include <QVBoxLayout>
#include "StackedView.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set up QSettings for your application
    QCoreApplication::setOrganizationName("QuickTurns");
    QCoreApplication::setApplicationName("QuickTurns");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, app.applicationDirPath());

    // Check if the folder path is already set
    QSettings settings;
    QString folderPath = settings.value("folderPath").toString();

    // Prompt the user to select a folder if the folder path is not set
    if (folderPath.isEmpty()) {
        QPushButton* button = new QPushButton("Select a folder to store books and metadata");
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(button);
        QWidget* widget = new QWidget;
        widget->setLayout(layout);
        widget->show();

        QObject::connect(button, &QPushButton::clicked, [&]() {
            QString newFolderPath = QFileDialog::getExistingDirectory(nullptr, "Select a folder to store books and metadata");
            if (!newFolderPath.isEmpty()) {
                settings.setValue("folderPath", newFolderPath);
                StackedView *stackedView = new StackedView(newFolderPath); // Pass the folder path to StackedView
                stackedView->show();
                widget->close();
            }
        });

        return app.exec();
    }

    StackedView stackedView(folderPath); // Pass the folder path to StackedView
    stackedView.show();
    return app.exec();
}
