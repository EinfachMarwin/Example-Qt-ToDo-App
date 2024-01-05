//
// Created by Marwin Nowak on 18.11.23.
//

#include "windows/mainwindow.h"

#include <widgets/listwidget.h>
#include <widgets/taskwidget.h>
#include <windows/settingswindow.h>

#include "dbmanager.h"

// Constructor for the main window
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("ToDo List");

    // Create a central widget
    auto* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    // Set minimum size for the central widget
    mainWidget->setMinimumSize(800, 600);


    // Create a main layout for the central widget
    auto* mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create a Widget for the sidebar
    auto* sidebarWidget = new QWidget(this);
    sidebarWidget->setStyleSheet("background-color: #1e1f26;");
    sidebarWidget->setFixedWidth(55);
    mainLayout->addWidget(sidebarWidget);

    // Create a layout for the sidebar
    auto* sidebarLayout = new QVBoxLayout(sidebarWidget);
    sidebarLayout->setContentsMargins(2, 2, 2, 15);

    //TODO Change appearance of the tooltips
    //TODO Error handling for Image loading
    // Create a label for the logo in the sidebar
    const QPixmap appLogo(":res/images/LogoToDoAppTransparent.png");
    const QPixmap scaledAppLogo = appLogo.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    auto* logoLabel = new QLabel(this);
    logoLabel->setGeometry(QRect(0, 0, 48, 48));
    logoLabel->setPixmap(scaledAppLogo);
    sidebarLayout->addWidget(logoLabel);
    sidebarLayout->setAlignment(logoLabel, Qt::AlignCenter);

    //TODO add hover effect to the buttons
    //TODO add click effect to the buttons
    // Create a button for the Tasks Window in the sidebar
    auto* tasksButton = new QPushButton(this);
    tasksButton->setStyleSheet("border: none; background-color: #1e1f26;");
    tasksButton->setIcon(QIcon(":res/images/TasksListIcon.png"));
    tasksButton->setToolTip("Tasks");
    tasksButton->setIconSize(QSize(32, 32));
    tasksButton->setGeometry(QRect(9, 9, 32, 32));
    sidebarLayout->addWidget(tasksButton);
    sidebarLayout->addStretch();
    sidebarLayout->setAlignment(tasksButton, Qt::AlignTop);

    // Ceate a help button in the sidebar
    auto* helpButton = new QPushButton(this);
    helpButton->setStyleSheet("border: none; background-color: #1e1f26;");
    helpButton->setIcon(QIcon(":res/images/HelpIcon.png"));
    helpButton->setToolTip("Help");
    helpButton->setIconSize(QSize(32, 32));
    helpButton->setGeometry(QRect(9, 9, 32, 32));
    sidebarLayout->addWidget(helpButton);

    // Create a settings button in the sidebar
    auto* settingsButton = new QPushButton(this);
    settingsButton->setStyleSheet("border: none; background-color: #1e1f26;");
    settingsButton->setIcon(QIcon(":res/images/SettingsIcon.png"));
    settingsButton->setToolTip("Settings");
    settingsButton->setIconSize(QSize(32, 32));
    settingsButton->setGeometry(QRect(9, 9, 32, 32));
    sidebarLayout->addWidget(settingsButton);

    // connect the buttons to their respective functions
    connect(helpButton, &QPushButton::clicked, this, &MainWindow::onHelpButtonClicked);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);
    connect(tasksButton, &QPushButton::clicked, this, &MainWindow::onTasksButtonClicked);

    // Addd the list widget and the task widget to the main layout
    auto* listWidget = new ListWidget(mainWidget);
    auto* taskWidget = new TaskWidget(mainWidget);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(taskWidget);

    // Open the Inbox list and set the name
    taskWidget->showTasksForListId1();
    taskWidget->setListName("Inbox");
}

// Function handles help button click
void MainWindow::onHelpButtonClicked()
{
    // Open the help page in the default browser
    QDesktopServices::openUrl(QUrl("https://github.com/EinfachMarwin"));
    qDebug() << "Help button clicked";
}

// Function handles settings button click
void MainWindow::onSettingsButtonClicked()
{
    // Open the settings window
    auto* settingsWindow = new SettingsWindow();
    settingsWindow->exec();
    qDebug() << "Settings button clicked";
}

// Function handles tasks button click
void MainWindow::onTasksButtonClicked()
{
    qDebug() << "Tasks button clicked";
}

// Destructor for the main window
MainWindow::~MainWindow()
{
}



// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "windows/moc_mainwindow.cpp"
