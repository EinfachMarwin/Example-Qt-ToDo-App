//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/taskwidget.h"
#include "database/models/task.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QScrollArea>
#include <QDateEdit>


TaskWidget::TaskWidget(QWidget* parent) : QWidget(parent)
{
    auto* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #ffffff;");
    mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Set policy to expanding

    taskListWidget = new QListWidget(this);
    taskListWidget->setLayout(new QVBoxLayout());
    taskListWidget->setFrameShape(QFrame::NoFrame);

    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* headerWidget = createHeaderWidget();
    mainLayout->addWidget(headerWidget);

    // Add the task list widget to the layout right after the header widget
    mainLayout->addWidget(taskListWidget);

    refreshTaskList();

    parent->layout()->addWidget(mainWidget);
}

TaskWidget::~TaskWidget()
{
}

QWidget* TaskWidget::createHeaderWidget()
{
    // Create a header widget
    auto* headerWidget = new QWidget(this);
    headerWidget->setFixedHeight(100);

    // Create a layout for the header widget
    auto* headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setContentsMargins(5, 0, 0, 0);
    headerLayout->setAlignment(Qt::AlignTop);
    headerLayout->setContentsMargins(10, 10, 10, 10);

    // Create a label for the header widget
    headerLabel = new QLabel(headerWidget);
    headerLabel->setText("<LISTNAME HERE>");
    headerLabel->setStyleSheet("color: #1e1f26; font-size: 20px; font-weight: bold;");
    headerLayout->addWidget(headerLabel);

    // Create line edit to add new tasks
    addTaskLineEdit = new QLineEdit(this);
    addTaskLineEdit->setStyleSheet("background-color: #d0e1f9; color: #283655; font-size: 16px; border-radius: 5px;");
    addTaskLineEdit->setContentsMargins(4, 4, 4, 4);
    addTaskLineEdit->setPlaceholderText(tr("Add a new task... press enter to save"));
    addTaskLineEdit->setFixedHeight(40);
    headerLayout->addSpacing(1);
    headerLayout->addWidget(addTaskLineEdit);

    // Connect the returnPressed signal to the addTask slot
    connect(addTaskLineEdit, &QLineEdit::returnPressed, this, &TaskWidget::returnPressed);

    return headerWidget;
}

void TaskWidget::refreshTaskList()
{
    // Remove all items from the task list widget
    QLayout* layout = taskListWidget->layout();
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        // Delete the widget
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    QVector<Task> tasks = Task::getTasksByListId(1);
    qDebug() << "Number of tasks fetched from database: " << tasks.size();

    // Create a scroll area
    auto* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);

    // Create a widget for the scroll area
    auto* scrollWidget = new QWidget;
    auto* scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setAlignment(Qt::AlignTop);

    // Add all tasks to the task list widget
    for (const Task& task : tasks)
    {
        QWidget* taskWidget = createTaskWidget(task);
        scrollLayout->addWidget(taskWidget);
    }

    // Set the widget for the scroll area
    scrollArea->setWidget(scrollWidget);

    // Add the scroll area to the task list widget
    taskListWidget->layout()->addWidget(scrollArea);
    taskListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    taskListWidget->layout()->setAlignment(Qt::AlignTop);
    taskListWidget->layout()->setContentsMargins(0, 0, 0, 0);
    taskListWidget->layout()->setSpacing(20);
    taskListWidget->layout()->update();
    taskListWidget->layout()->activate();
}

void TaskWidget::returnPressed()
{
    qDebug() << "Return pressed";
    QString taskName = addTaskLineEdit->text();
    qDebug() << "Task name";

    if (!taskName.trimmed().isEmpty()) {
        // Create a new task
        Task task;
        qDebug() << "Task created";
        task.description = taskName.toStdString();
        task.is_done = false;
        task.list_id = 1;
        qDebug() << "Task description";

        // Save the task in the database
        task.save();
        qDebug() << "Task saved";

        // Refresh the task list
        refreshTaskList();
    }

    // Clear the line edit
    addTaskLineEdit->clear();
    qDebug() << "Line edit cleared";
}

QWidget* TaskWidget::showTasksForListId1()
{
    auto* containerWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(containerWidget);

    QVector<Task> tasks = Task::getTasksByListId(1);
    for (const Task& task : tasks)
    {
        QWidget* taskWidget = createTaskWidget(task);
        layout->addWidget(taskWidget);
    }
    return containerWidget;
}

QWidget* TaskWidget::createTaskWidget(const Task& task)
{
    // Create a new widget for the task
    auto* taskWidget = new QWidget(this);

    // Create a layout for the task widget with no margins
    auto* layout = new QHBoxLayout(taskWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create a checkbox for the task status
    auto* statusCheckbox = new QCheckBox(taskWidget);
    statusCheckbox->setChecked(task.is_done);
    layout->addWidget(statusCheckbox);
    layout->setAlignment(statusCheckbox, Qt::AlignVCenter);

    // Create a label for the task description
    auto* descriptionLabel = new QLabel(QString::fromStdString(task.description), taskWidget);
    descriptionLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(descriptionLabel);
    layout->setAlignment(descriptionLabel, Qt::AlignVCenter);
    layout->addStretch();

    // Create a date edit for the task deadline
    auto* deadlineEdit = new QDateEdit(task.deadline.empty() ? QDate::currentDate() : QDate::fromString(QString::fromStdString(task.deadline), "yyyy-MM-dd"), taskWidget);
    deadlineEdit->setDisplayFormat("dd.MM.yyyy");
    deadlineEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    layout->addWidget(deadlineEdit);
    layout->setAlignment(deadlineEdit, Qt::AlignVCenter);

    // Create a delete button for the task
    auto* deleteButton = new QPushButton(tr("Delete"), taskWidget);
    deleteButton->setMaximumWidth(50);
    layout->addWidget(deleteButton);
    layout->setAlignment(deleteButton, Qt::AlignVCenter);

    // Connect the checkbox's stateChanged signal to a slot that deletes the task if checked
    connect(statusCheckbox, &QCheckBox::stateChanged, this, [this, task](int state)
    {
        if (state == Qt::Checked) {
            Task::deleteTask(task.id);
            refreshTaskList();
        }
    });

    // Connect the date edit's dateChanged signal to a slot that updates the task deadline
    connect(deadlineEdit, &QDateEdit::dateChanged, this, [this, task](const QDate& date)
    {
        Task::updateTaskDeadline(task.id, date.toString("yyyy-MM-dd").toStdString());
        refreshTaskList();
    });

    // Connect the delete button's clicked signal to a slot that deletes the task
    connect(deleteButton, &QPushButton::clicked, this, [this, task]()
    {
        Task::deleteTask(task.id);
        refreshTaskList();
    });

    return taskWidget;
}

void TaskWidget::setListName(const QString& listName)
{
    headerLabel->setText(listName);
}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_taskwidget.cpp"
