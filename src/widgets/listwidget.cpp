//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/listwidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <database/models/list.h>

ListWidget::ListWidget(QWidget* parent) : QWidget(parent)
{
    // Create main Widget
    auto* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #283655;");
    mainWidget->setMinimumSize(QSize(200, 800));  // Increase the minimum size

    // Create main layout
    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 20);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(createHeaderWidget());

    // Create a widget for "Important, Today and Inbox"
    auto* menuWidget = createMenuWidget();
    mainLayout->addWidget(menuWidget);  // Add the menu widget to the main layout

    // Create a widget for the list layout
    auto* listWidget = new QWidget(this);
    listLayout = new QVBoxLayout(listWidget);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setAlignment(Qt::AlignTop);  // Set alignment to top
    mainLayout->addWidget(listWidget);  // Add the list widget to the main layout

    refreshListWidget();  // Add this line

    parent->layout()->addWidget(mainWidget);
}

ListWidget::~ListWidget()
{
}

QWidget* ListWidget::createHeaderWidget()
{
    // Create a header widget
    auto* headerWidget = new QWidget(this);
    headerWidget->setMaximumHeight(50);

    // Create a layout for the header widget
    auto* headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(5, 0, 0, 0);

    // Create a label for the header widget
    auto* headerLabel = new QLabel(headerWidget);
    headerLabel->setText("ShowToDo");
    headerLabel->setStyleSheet("color: #d0e1f9; font-size: 20px; font-weight: bold;");
    headerLayout->addWidget(headerLabel);
    headerLayout->setAlignment(headerLabel, Qt::AlignLeft);

    return headerWidget;
}

QWidget* ListWidget::createMenuWidget()
{
    // Create a list widget
    auto* listWidget = new QWidget(this);
    resize(QSize(110, 600));

    // Create a layout for the list widget
    listLayout = new QVBoxLayout(listWidget);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setAlignment(Qt::AlignTop);  // Set alignment to top

    // Create a widget for "Important, Today and Inbox"
    auto* menuWidget = new QWidget(listWidget);
    menuWidget->setFixedHeight(90);
    menuWidget->setMinimumWidth(140);

    // Create a layout for the menu widget
    auto* menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setContentsMargins(10, 10, 10, 10);

    // Create button for "Important"
    const auto* importantButton = createMenuButton("  IMPORTANT", ":res/images/ImportantIcon.png", menuLayout);
    // Create button for "Today"
    const auto* todayButton = createMenuButton("  TODAY", ":res/images/TodayIcon.png", menuLayout);
    // Create button for "Inbox"
    const auto* inboxButton = createMenuButton("  INBOX", ":res/images/InboxIcon.png", menuLayout);

    // Connect the buttons to the slots
    connect(importantButton, &QPushButton::clicked, this, &ListWidget::onImportantButtonClicked);
    connect(todayButton, &QPushButton::clicked, this, &ListWidget::onTodayButtonClicked);
    connect(inboxButton, &QPushButton::clicked, this, &ListWidget::onInboxButtonClicked);

    return listWidget;
}

QPushButton* ListWidget::createMenuButton(const QString& buttonName, const QString& iconPath, QLayout* parent)
{
    // Create a button for the list widget
    auto* menuButton = new QPushButton(this);
    menuButton->setText(buttonName);
    menuButton->setStyleSheet("border: none; color: #ffffff; font-size: 13px; font-weight: bold;");
    menuButton->setIcon(QIcon(iconPath));
    menuButton->setIconSize(QSize(17, 17));
    parent->addWidget(menuButton);
    parent->setAlignment(menuButton, Qt::AlignLeft);

    return menuButton;
}

void ListWidget::refreshListWidget()
{
    // Remove all items from the list widget
    QLayoutItem* item;
    while ((item = listLayout->takeAt(0)) != nullptr)
    {
        // Delete the widget
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    // Create a button for "Add List"
    auto* addListButton = new QPushButton(this);
    addListButton->setText("Add List");
    addListButton->setStyleSheet("border: none; color: #ffffff; font-size: 13px; font-weight: bold;");
    listLayout->addWidget(addListButton);
    listLayout->setContentsMargins(10, 10, 10, 10);

    connect(addListButton, &QPushButton::clicked, this, &ListWidget::onAddButtonClicked);

    QVector<List> lists = List::getAllLists();
    for (const List& list : lists)
    {
        auto* listContainer = new QWidget(this);
        listContainer->setFixedHeight(30);  // Set the height of the list container
        auto* listContainerLayout = new QHBoxLayout(listContainer);
        listContainerLayout->setContentsMargins(0, 0, 0, 0);
        listContainerLayout->setAlignment(Qt::AlignTop);

        auto* listButton = createMenuButton(QString::fromStdString(list.name), "", listContainerLayout);  // Remove the icon
        connect(listButton, &QPushButton::clicked, this, [this, list]()
        {
            // TODO: Implement the behavior when a list button is clicked
        });

        auto* deleteButton = new QPushButton(this);
        deleteButton->setText("Delete");
        deleteButton->setStyleSheet("border: none; color: #ff0000; font-size: 13px; font-weight: bold;");
        listContainerLayout->addWidget(deleteButton);
        connect(deleteButton, &QPushButton::clicked, this, [this, list]()
        {
            onDeleteListButtonClicked(list.id);
        });

        listLayout->addWidget(listContainer);
    }
}

void ListWidget::onTodayButtonClicked()
{
    // TODO: Implement this method
    qDebug() << "Today button clicked";
}

void ListWidget::onImportantButtonClicked()
{
    //TODO: Implement this method
    qDebug() << "Important button clicked";
}

void ListWidget::onInboxButtonClicked()
{
    //TODO: Implement this method
    qDebug() << "Inbox button clicked";
}

void ListWidget::onAddButtonClicked()
{
    bool ok;
    QString listName = QInputDialog::getText(this, tr("New List"),
                                             tr("List name:"), QLineEdit::Normal,
                                             "", &ok);
    if (ok && !listName.isEmpty()) {
        List newList;
        newList.name = listName.toStdString();
        newList.save();
        refreshListWidget();
    }
}

void ListWidget::onDeleteListButtonClicked(int listId)
{
    List::deleteList(listId);
    refreshListWidget();
}
// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_listwidget.cpp"
