//
// Created by Marwin Nowak on 26.11.23.
//

#include "windows/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
    // Set window title
    setWindowTitle("ToDo-Settings");
    // Create main Widget
    auto* mainWidget = new QWidget(this);
    mainWidget->setFixedSize(QSize(500, 400));

    // Create main layout
    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
}

SettingsWindow::~SettingsWindow()
{
}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "windows/moc_settingswindow.cpp"
