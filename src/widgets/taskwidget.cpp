//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/taskwidget.h"
#include "database/models/task.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>


TaskWidget::TaskWidget(QWidget* parent) : QWidget(parent)
{
    auto* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #ffffff;");
    mainWidget->setMinimumSize(QSize(250, 600));

    taskListWidget = new QListWidget(this);
    taskListWidget->setLayout(new QVBoxLayout());

    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(createHeaderWidget());

    refreshTaskList();  // Refresh the task list

    mainLayout->addWidget(taskListWidget);  // Add the task list widget to the layout

    parent->layout()->addWidget(mainWidget);
}

TaskWidget::~TaskWidget()
{
}

QWidget* TaskWidget::createHeaderWidget()
{
    // Create a header widget
    auto* headerWidget = new QWidget(this);
    headerWidget->setFixedHeight(250);

    // Create a layout for the header widget
    auto* headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setContentsMargins(5, 0, 0, 0);
    headerLayout->setAlignment(Qt::AlignTop);
    headerLayout->setContentsMargins(10, 10, 10, 10);

    // Create a label for the header widget
    headerLabel = new QLabel(headerWidget); // Verwenden Sie das Mitglied headerLabel
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
    // Löschen Sie alle aktuellen Aufgabenwidgets
    QLayout* layout = taskListWidget->layout();
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item->widget(); // Delete the widget
    }

    QVector<Task> tasks = Task::getTasksByListId(1);
    qDebug() << "Number of tasks fetched from database: " << tasks.size();

    // Add all tasks to the task list widget
    for (const Task& task : tasks)
    {
        QWidget* taskWidget = createTaskWidget(task);
        taskListWidget->layout()->addWidget(taskWidget);
    }

    taskListWidget->layout()->update();
    taskListWidget->layout()->activate();
}

void TaskWidget::returnPressed()
{
    qDebug() << "Return pressed";
    QString taskName = addTaskLineEdit->text();
    qDebug() << "Task name";

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
    QWidget* taskWidget = new QWidget(this);

    // Create a layout for the task widget
    QHBoxLayout* layout = new QHBoxLayout(taskWidget);

    // Create a checkbox for the task status
    QCheckBox* statusCheckbox = new QCheckBox(taskWidget);
    statusCheckbox->setChecked(task.is_done);
    layout->addWidget(statusCheckbox);
    layout->setAlignment(statusCheckbox, Qt::AlignVCenter);

    // Create a label for the task description
    QLabel* descriptionLabel = new QLabel(QString::fromStdString(task.description), taskWidget);
    descriptionLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(descriptionLabel);
    layout->setAlignment(descriptionLabel, Qt::AlignVCenter);
    layout->addStretch();

    // Create a label for the task deadline
    QLabel* deadlineLabel = new QLabel(QString::fromStdString(task.deadline), taskWidget);
    deadlineLabel->setText(QString::fromStdString(task.deadline));
    deadlineLabel->setAlignment(Qt::AlignRight);
    deadlineLabel->setStyleSheet("color: #1e1f26; font-size: 16px; font-weight: bold;");
    layout->addWidget(deadlineLabel);
    layout->setAlignment(deadlineLabel, Qt::AlignVCenter);

    // Create a delete button for the task
    QPushButton* deleteButton = new QPushButton(tr("Delete"), taskWidget);
    deleteButton->setMaximumWidth(50);
    layout->addWidget(deleteButton);
    layout->setAlignment(deleteButton, Qt::AlignVCenter);

    // Connect the checkbox's stateChanged signal to a slot that updates the task's status
    connect(statusCheckbox, &QCheckBox::stateChanged, this, [this, task](int state)
    {
        Task::updateTaskStatus(task.id, state == Qt::Checked);
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
