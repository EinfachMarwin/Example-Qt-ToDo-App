//
// Created by Marwin Nowak on 26.11.23.
//

#include "windows/settingswindow.h"

#include <QLabel>
#include <QComboBox>
#include <qcoreapplication.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QTranslator>

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
    // Set window title
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

    // Create a widget for language selection
    auto* languageWidget = new QWidget(mainWidget);
    auto* languageLayout = new QHBoxLayout(languageWidget);
    languageLayout->setContentsMargins(20, 20, 20, 20);

    // Create a label for language selection
    auto* languageLabel = new QLabel(languageWidget);
    languageLabel->setText(tr("Language"));
    languageLayout->addWidget(languageLabel);

    // Initialize languageDropdown
    languageDropdown = new QComboBox(languageWidget);
    languageDropdown->addItem(tr("English"));
    languageDropdown->addItem(tr("German"));

    languageLayout->addWidget(languageDropdown);

    // Connect the signal for language change
    connect(languageDropdown, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [this](int index){
            // Get the selected language
            QString selectedLanguage = languageDropdown->itemText(index);

            // Save the selected language
            saveSettings();

            // Reload the application
            reloadApplication();
        });

    mainLayout->addWidget(languageWidget);

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
    qDebug() << "close button clicked";
}

void SettingsWindow::changeLanguage(const QString& language)
{
    static QTranslator translator;

    // Unload the current translation
    qApp->removeTranslator(&translator);

    // Load the new translation
    if (translator.load(":/translations/ToDo_" + language)) {
        qApp->installTranslator(&translator);
    } else {
        qWarning() << "Could not load translation file for language:" << language;
    }
}

void SettingsWindow::saveLanguageSetting(const QString& language)
{
    // Open the configuration file
    QFile configFile("config.ini");
    if (!configFile.open(QIODevice::WriteOnly)) {
        qWarning("Could not open config file for writing");
        return;
    }

    // Write the selected language to the configuration file
    QTextStream out(&configFile);
    out << "language=" << language;

    configFile.close();

    qDebug() << "Language setting saved";
}

void SettingsWindow::saveSettings()
{
    // Get the selected language from the dropdown
    QString selectedLanguage = languageDropdown->currentText();

    // Save the selected language
    saveLanguageSetting(selectedLanguage);

    // Change the language
    changeLanguage(selectedLanguage);

    // Reload the application
    reloadApplication();
}

void SettingsWindow::reloadApplication()
{
    // Close the current application
    qApp->quit();

    // Start a new instance of the application
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "windows/moc_settingswindow.cpp"