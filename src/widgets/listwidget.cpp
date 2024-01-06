//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/listwidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QDockWidget>
#include <QScrollArea>
#include <QMessageBox>
#include <database/models/list.h>

ListWidget::ListWidget(QWidget* parent) : QWidget(parent)
{
    // Create main Widget
    auto* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #283655;");
    mainWidget->setMinimumSize(QSize(200, 800));
    mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainWidget->setMaximumWidth(250);

    // Create main layout
    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 20);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(createHeaderWidget());

    // Create a widget for "Important, Today and Inbox"
    auto* menuWidget = new QWidget(this);
    menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(createMenuWidget());

    // Add a separator line
    auto* line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line);

    // Create a scroll area for the list layout
    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    mainLayout->addWidget(scrollArea);

    // Create a widget for the list layout
    auto* listWidget = new QWidget(this);
    listLayout = new QVBoxLayout(listWidget);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setAlignment(Qt::AlignTop);
    scrollArea->setWidget(listWidget);

    refreshListWidget();

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
    headerLayout->setContentsMargins(5, 10, 0, 0);

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
    listWidget->setFixedHeight(90);

    // Create a layout for the list widget
    listLayout = new QVBoxLayout(listWidget);
    listLayout->setContentsMargins(5, 0, 0, 0);
    listLayout->setAlignment(Qt::AlignTop);

    // Create a widget for "Important, Today and Inbox"
    auto* menuWidget = new QWidget(listWidget);
    menuWidget->setFixedHeight(100);
    listLayout->addWidget(menuWidget);

    // Create a layout for the menu widget
    menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setContentsMargins(10, 10, 0, 10);

    // Create button for "Today"
    const auto* todayButton = createMenuButton("  TODAY", ":res/images/TodayIcon.png", menuLayout);
    // Create button for "Inbox"
    const auto* inboxButton = createMenuButton("  INBOX", ":res/images/InboxIcon.png", menuLayout);

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

    QVector<List> lists = List::getAllLists();
    for (const List& list : lists)
    {
        // Skip the "Inbox" list
        if (list.name == "Inbox") {
            continue;
        }

        auto* listContainer = new QWidget(this);
        listContainer->setFixedHeight(30);
        auto* listContainerLayout = new QHBoxLayout(listContainer);
        listContainerLayout->setContentsMargins(0, 0, 0, 0);
        listContainerLayout->setAlignment(Qt::AlignTop);

        auto* listButton = createMenuButton(QString::fromStdString(list.name), "", listContainerLayout);

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

    listLayout->setSpacing(2);
    listLayout->addStretch();

    // Create a button for "Add List"
    auto* addListButton = new QPushButton(this);
    addListButton->setText("Add List");
    addListButton->setStyleSheet("border: none; color: #ffffff; font-size: 13px; font-weight: bold;");
    listLayout->addWidget(addListButton);
    listLayout->setContentsMargins(20, 10, 10, 10);

    connect(addListButton, &QPushButton::clicked, this, &ListWidget::onAddButtonClicked);
}

void ListWidget::onTodayButtonClicked()
{
    // TODO: Implement this method
    qDebug() << "Today button clicked";
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
        std::string listNameStd = listName.toStdString();
        if (listNameStd == "Inbox" || List::nameExists(listNameStd)) {
            QMessageBox::warning(this, tr("Error"), tr("List name already exists or is reserved."));
        } else {
            List newList;
            newList.name = listNameStd;
            newList.save();
            refreshListWidget();
        }
    }
}

void ListWidget::onDeleteListButtonClicked(int listId)
{
    List::deleteList(listId);
    refreshListWidget();
}
// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_listwidget.cpp"
