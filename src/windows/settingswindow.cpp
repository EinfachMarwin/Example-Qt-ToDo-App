//
// Created by Marwin Nowak on 26.11.23.
//

#include "windows/settingswindow.h"

#include <QComboBox>
#include <qcoreapplication.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include <windows/mainwindow.h>

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
    // Set window title and size and margins
    setWindowTitle(tr("ToDo-Settings"));
    setFixedSize(QSize(350, 200));
    setContentsMargins(20, 20, 20, 20);

    // Create main Widget
    auto* mainWidget = new QWidget(this);
    mainWidget->setFixedSize(QSize(350, 200));
    mainWidget->setStyleSheet("background-color: #FFFFFF;");

    // Create main layout
    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create a header widget
    auto* headerWidget = new QWidget(this);
    headerWidget->setMaximumHeight(50);
    headerWidget->setStyleSheet("background-color: #283655;");

    // Create a layout for the header widget
    auto* headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(5, 0, 0, 0);

    // Create a label for the header widget
    auto* headerLabel = new QLabel(headerWidget);
    headerLabel->setText(tr("Settings"));
    headerLabel->setStyleSheet("color: #d0e1f9; font-size: 20px; font-weight: bold;");
    headerLayout->addWidget(headerLabel);
    headerLayout->setAlignment(headerLabel, Qt::AlignLeft);

    // Add the header widget to the main layout
    mainLayout->addWidget(headerWidget);

    // Create a widget for default deadline selection
    auto* defaultDeadlineWidget = new QWidget(mainWidget);
    auto* defaultDeadlineLayout = new QHBoxLayout(defaultDeadlineWidget);
    defaultDeadlineLayout->setContentsMargins(20, 20, 20, 20);

    // Create a label for default deadline selection
    auto* defaultDeadlineLabel = new QLabel(defaultDeadlineWidget);
    defaultDeadlineLabel->setText(tr("Standard Deadline"));
    defaultDeadlineLayout->addWidget(defaultDeadlineLabel);

    // Initialize defaultDeadlineDropdown
    defaultDeadlineDropdown = new QComboBox(defaultDeadlineWidget);
    defaultDeadlineDropdown->addItem(tr("Same day"));
    defaultDeadlineDropdown->addItem(tr("In three days"));
    defaultDeadlineDropdown->addItem(tr("In one week"));

    // Load the selected default deadline
    int defaultDeadlineDays = loadDefaultDeadlineSetting();
    QString defaultDeadline = QString::number(defaultDeadlineDays);
    int index = defaultDeadlineDropdown->findText(defaultDeadline);
    if (index != -1) {
        defaultDeadlineDropdown->setCurrentIndex(index);
    }
    // Add the default deadline dropdown to the layout
    defaultDeadlineLayout->addWidget(defaultDeadlineDropdown);
    mainLayout->addWidget(defaultDeadlineWidget);
    mainLayout->addStretch();

    // Create a widget for the buttons
    auto* buttonsWidget = new QWidget(this);
    auto* buttonsLayout = new QHBoxLayout(buttonsWidget);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);

    // Create Apply, OK and Cancel buttons
    auto* applyButton = new QPushButton(tr("Apply"), buttonsWidget);
    auto* okButton = new QPushButton(tr("OK"), buttonsWidget);
    auto* cancelButton = new QPushButton(tr("Cancel"), buttonsWidget);

    // Add the buttons to the layout
    buttonsLayout->addWidget(applyButton);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    buttonsLayout->setContentsMargins(20, 20, 20, 20);

    // Add the buttons widget to the main layout
    mainLayout->addWidget(buttonsWidget);

    // Connect the buttons to the corresponding slots
    connect(applyButton, &QPushButton::clicked, this, &SettingsWindow::saveSettings);
    connect(okButton, &QPushButton::clicked, this, &SettingsWindow::closeSettings);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsWindow::closeSettings);
}

SettingsWindow::~SettingsWindow()
{
    qDebug() << "Settings window closed";
}

void SettingsWindow::closeSettings()
{
    // Get the selected default deadline from the dropdown
    QString selectedDefaultDeadlineText = defaultDeadlineDropdown->currentText();
    int selectedDefaultDeadline = 0;

    // Check if the selected default deadline is different from the current default deadline
    if (selectedDefaultDeadline != loadDefaultDeadlineSetting()) {
        // Create a message box to ask the user if they want to save the changes
        QMessageBox messageBox;
        messageBox.setWindowTitle(tr("Save changes?"));
        messageBox.setText(tr("The default deadline has been changed. Do you want to save the changes?"));
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setDefaultButton(QMessageBox::Yes);
        int response = messageBox.exec();

        // If the user clicked "Yes", save the changes
        if (response == QMessageBox::Yes) {
            saveSettings();
        }
    }

    // Close the settings window
    this->close();
}

int SettingsWindow::loadDefaultDeadlineSetting()
{
    // Path to the configuration file
    QString configFilePath = "config.ini";

    // Check if the configuration file exists
    if (!QFile::exists(configFilePath)) {
        // If the file does not exist, create it
        QFile configFile(configFilePath);
        if (!configFile.open(QIODevice::WriteOnly)) {
            qWarning() << "Could not create config file";
            return 0;  // Return default deadline if config file cannot be created
        }
        // Write the default deadline to the configuration file
        QTextStream out(&configFile);
        out << "defaultDeadline=0";
        configFile.close();
    }

    // Open the configuration file
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open config file for reading";
        return 0;  // Return default deadline if config file does not exist
    }

    // Read the default deadline from the configuration file
    QTextStream in(&configFile);
    int defaultDeadline = 0;
    QString line;
    while (in.readLineInto(&line)) {
        if (line.startsWith("defaultDeadline=")) {
            QString deadline = line.split("=")[1];
            defaultDeadline = deadline.toInt();
            break;
        }
    }

    configFile.close();

    qDebug() << "Default deadline setting loaded: " << defaultDeadline;

    return defaultDeadline;
}

// Function to save the settings
void SettingsWindow::saveSettings()
{
    // Get the selected default deadline from the dropdown
    QString selectedDefaultDeadlineText = defaultDeadlineDropdown->currentText();
    int selectedDefaultDeadline = 0;
    if (selectedDefaultDeadlineText == "Same day") {
        selectedDefaultDeadline = 0;
    } else if (selectedDefaultDeadlineText == "In three days") {
        selectedDefaultDeadline = 3;
    } else if (selectedDefaultDeadlineText == "In one week") {
        selectedDefaultDeadline = 7;
    }
    // Save the selected default deadline
    saveDefaultDeadlineSetting(selectedDefaultDeadline);

    // Reload the application
    reloadApplication();
}

// Function to save the selected default deadline
void SettingsWindow::saveDefaultDeadlineSetting(int defaultDeadline)
{
    // Open the configuration file
    QFile configFile("config.ini");
    if (!configFile.open(QIODevice::WriteOnly)) {
        qWarning("Could not open config file for writing");
        return;
    }

    // Write the selected default deadline to the configuration file
    QTextStream out(&configFile);
    out << "defaultDeadline=" << defaultDeadline;

    // Close the configuration file
    configFile.close();

    qDebug() << "Default deadline setting saved";
}

// Function to reload the application
void SettingsWindow::reloadApplication()
{
    this->update();
}


// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "windows/moc_settingswindow.cpp"