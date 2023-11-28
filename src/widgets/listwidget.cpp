//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/listwidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ListWidget::ListWidget(QWidget *parent) : QWidget(parent) {
    // Create main Widget
    auto *mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #283655;");
    mainWidget->setMinimumSize(QSize(200, 600));
    mainWidget->setMaximumWidth(300);

    // Create main layout
    auto *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(createHeaderWidget());
    mainLayout->addWidget(createMenuWidget());
    parent->layout()->addWidget(mainWidget);
}

ListWidget::~ListWidget() {
}

QWidget* ListWidget::createHeaderWidget() {
    // Create a header widget
    auto *headerWidget = new QWidget(this);
    headerWidget->setMaximumHeight(50);

    // Create a layout for the header widget
    auto *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(5, 0, 0, 0);

    // Create a label for the header widget
    auto *headerLabel = new QLabel(headerWidget);
    headerLabel->setText("ShowToDo");
    headerLabel->setStyleSheet("color: #d0e1f9; font-size: 20px; font-weight: bold;");
    headerLayout->addWidget(headerLabel);
    headerLayout->setAlignment(headerLabel, Qt::AlignLeft);

    return headerWidget;
}

QWidget* ListWidget::createMenuWidget() {
    // Create a list widget
    auto *listWidget = new QWidget(this);
    resize(QSize(110, 600));

    // Create a layout for the list widget
    auto *listLayout = new QVBoxLayout(listWidget);
    listLayout->setContentsMargins(0, 0, 0, 0);

    // Create a widget for "Important, Today and Inbox"
    auto *menuWidget = new QWidget(listWidget);
    menuWidget->setFixedHeight(90);
    menuWidget->setMinimumWidth(140);

    // Create a layout for the menu widget
    auto *menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setContentsMargins(10, 10, 10, 10);

    // Create button for "Important"
    const auto *importantButton = createMenuButton("  IMPORTANT", ":res/images/ImportantIcon.png", menuLayout);
    // Create button for "Today"
    const auto *todayButton = createMenuButton("  TODAY", ":res/images/TodayIcon.png", menuLayout);
    // Create button for "Inbox"
    const auto *inboxButton = createMenuButton("  INBOX", ":res/images/InboxIcon.png", menuLayout);

    // Connect the buttons to the slots
    connect(importantButton, &QPushButton::clicked, this, &ListWidget::onImportantButtonClicked);
    connect(todayButton, &QPushButton::clicked, this, &ListWidget::onTodayButtonClicked);
    connect(inboxButton, &QPushButton::clicked, this, &ListWidget::onInboxButtonClicked);

    return listWidget;
}

QPushButton* ListWidget::createMenuButton(const QString& buttonName, const QString& iconPath, QLayout* parent) {
    // Create a button for the list widget
    auto *menuButton = new QPushButton(this);
    menuButton->setText(buttonName);
    menuButton->setStyleSheet("border: none; color: #ffffff; font-size: 13px; font-weight: bold;");
    menuButton->setIcon(QIcon(iconPath));
    menuButton->setIconSize(QSize(17, 17));
    parent->addWidget(menuButton);
    parent->setAlignment(menuButton, Qt::AlignLeft);

    return menuButton;
}

void ListWidget::onTodayButtonClicked() {
    // TODO: Implement this method
    qDebug() << "Today button clicked";
}

void ListWidget::onImportantButtonClicked() {
    //TODO: Implement this method
    qDebug() << "Important button clicked";
}

void ListWidget::onInboxButtonClicked() {
    //TODO: Implement this method
    qDebug() << "Inbox button clicked";
}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_listwidget.cpp"