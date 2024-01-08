//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/taskwidget.h"
#include "database/models/task.h"

#include <QLabel>
#include <QCheckBox>
#include <QScrollArea>
#include <QDateEdit>
#include <QInputDialog>
#include <database/models/list.h>
#include <windows/settingswindow.h>


TaskWidget::TaskWidget(QWidget* parent) : QWidget(parent)
{
    // Create a main widget
    auto* mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #ffffff;");
    mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create a task list widget
    taskListWidget = new QListWidget(this);
    taskListWidget->setLayout(new QVBoxLayout());
    taskListWidget->setFrameShape(QFrame::NoFrame);

    // Create a main layout for the main widget
    auto* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Create a header widget and add it to the main layout
    QWidget* headerWidget = createHeaderWidget();
    mainLayout->addWidget(headerWidget);
    mainLayout->addSpacing(21);

    // Add the task list widget to the layout right after the header widget
    mainLayout->addWidget(taskListWidget);

    // Set the current list ID to 1 (Inbox)
    refreshTaskList(1);

    // Add the main widget to the parent widget
    parent->layout()->addWidget(mainWidget);
}

// Destructor for the task widget
TaskWidget::~TaskWidget()
{
}

// Function creates a header widget for the task widget
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
    headerLayout->addSpacing(8);

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

// Function updates the task list widget with the given tasks
void TaskWidget::updateTaskList(const QVector<Task>& tasks)
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

// Function refreshes the task list widget with the tasks for the given list ID
void TaskWidget::refreshTaskList(int listId)
{
    // Check if the list exists
    QVector<List> lists = List::getAllLists();
    bool listExists = false;
    QString listName;
    for (const List& list : lists)
    {
        if (list.id == listId) {
            listExists = true;
            listName = QString::fromStdString(list.name);
            break;
        }
    }

    if (!listExists) {
        qDebug() << "List with ID " << listId << " does not exist";
        return;
    }

    // Set the current list ID
    setCurrentListId(listId);

    // Update the list name in the header label
    setListName(listName);

    // Get tasks for the list
    QVector<Task> tasks = Task::getTasksByListId(listId);

    // Update the task list
    updateTaskList(tasks);
}

// Function shows all tasks for today
void TaskWidget::showTasksForToday()
{
    // Get today's date
    QDate today = QDate::currentDate();

    // Set the current list ID to -1 (Today)
    setCurrentListId(-1);

    // Get all tasks
    QVector<Task> allTasks = Task::getAllTasks();

    // Filter tasks for today
    QVector<Task> tasksForToday;
    for (const Task& task : allTasks)
    {
        // Parse the task deadline
        QDate deadline = QDate::fromString(QString::fromStdString(task.deadline), "yyyy-MM-dd");

        // Check if the task deadline is today or in the past
        if (deadline <= today)
        {
            tasksForToday.append(task);
        }
    }

    // Update the task list
    updateTaskList(tasksForToday);

    // Set the list name to "Today"
    setListName("Today");
}

// Function handles the return pressed signal from the line edit
void TaskWidget::returnPressed()
{
    // Get the task name from the line edit
    qDebug() << "Return pressed";
    QString taskName = addTaskLineEdit->text();
    qDebug() << "Task name";

    // Check if the task name is empty
    if (!taskName.trimmed().isEmpty()) {
        // Get the current list ID
        int listId = getCurrentListId();

        // Create a new task
        Task task;
        task.description = taskName.toStdString();
        task.is_done = false;
        // If the list ID is -1, set it to 1 (Inbox)
        task.list_id = listId == -1 ? 1 : listId;

        // Get the default deadline from the settings
        SettingsWindow settings;
        int defaultDeadlineDays = settings.loadDefaultDeadlineSetting();

        // Get the current date and add the default deadline
        QDate currentDate = QDate::currentDate();
        QDate deadlineDate = currentDate.addDays(defaultDeadlineDays);
        // Set the task deadline to the default deadline
        task.deadline = deadlineDate.toString("yyyy-MM-dd").toStdString();

        // Save the task in the database
        task.save();
        qDebug() << "Task saved";

        // Refresh the task list
        refreshTaskList(task.list_id);
    }

    // Clear the line edit
    addTaskLineEdit->clear();
    qDebug() << "Line edit cleared";
}

// Function shows all tasks for the given list ID
QWidget* TaskWidget::showTasksForListId(int listId)
{
    // Create a container widget for the task list
    auto* containerWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(containerWidget);

    // Get all tasks for the given list ID
    QVector<Task> tasks = Task::getTasksByListId(listId);
    for (const Task& task : tasks)
    {
        QWidget* taskWidget = createTaskWidget(task);
        layout->addWidget(taskWidget);
    }

    // Set the current list ID
    setCurrentListId(listId);

    return containerWidget;
}

// Function creates a task widget for the given task
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

    // Check if the deadline is in the past
    QDate deadlineDate = QDate::fromString(QString::fromStdString(task.deadline), "yyyy-MM-dd");
    if (deadlineDate < QDate::currentDate()) {
        deadlineEdit->setStyleSheet("QDateEdit { color: red; }");
    }

    layout->addWidget(deadlineEdit);
    layout->setAlignment(deadlineEdit, Qt::AlignVCenter);

    // Create an edit button for the task
    auto* editButton = new QPushButton(taskWidget);
    editButton->setIcon(QIcon(":res/images/EditIcon.png"));
    editButton->setIconSize(QSize(24, 24));
    editButton->setStyleSheet("border: none; background-color: #ffffff;");
    editButton->setMaximumWidth(50);
    layout->addWidget(editButton);
    layout->setAlignment(editButton, Qt::AlignVCenter);

    // Create a delete button for the task
    auto* deleteButton = new QPushButton(taskWidget);
    deleteButton->setIcon(QIcon(":res/images/DeleteIcon.png"));
    deleteButton->setIconSize(QSize(24, 24));
    deleteButton->setStyleSheet("border: none; background-color: #ffffff;");
    deleteButton->setMaximumWidth(50);
    layout->addWidget(deleteButton);
    layout->setAlignment(deleteButton, Qt::AlignVCenter);

    // Connect the checkbox's stateChanged signal to a slot that deletes the task if checked
    connect(statusCheckbox, &QCheckBox::stateChanged, this, [this, task](int state)
    {
        if (state == Qt::Checked) {
            Task::deleteTask(task.id);
            refreshTaskList(task.list_id);
        }
    });

    // Connect the date edit's dateChanged signal to a slot that updates the task deadline
    connect(deadlineEdit, &QDateEdit::dateChanged, this, [this, task](const QDate& date)
    {
        Task::updateTaskDeadline(task.id, date.toString("yyyy-MM-dd").toStdString());
        refreshTaskList(task.list_id);
    });

    // Connect the edit button's clicked signal to a slot that edits the task
    connect(editButton, &QPushButton::clicked, this, [this, task, descriptionLabel]()
    {
        bool ok;
        QString newText = QInputDialog::getText(this, tr("Edit Task"),
                                                tr("Task description:"), QLineEdit::Normal,
                                                descriptionLabel->text(), &ok);
        if (ok && !newText.isEmpty()) {
            Task::updateTaskDescription(task.id, newText.toStdString());
            refreshTaskList(task.list_id);
        }
    });

    // Connect the delete button's clicked signal to a slot that deletes the task
    connect(deleteButton, &QPushButton::clicked, this, [this, task]()
    {
        Task::deleteTask(task.id);
        refreshTaskList(task.list_id);
    });

    return taskWidget;
}

// Function sets the task widget for the list widget
void TaskWidget::setListName(const QString& listName)
{
    headerLabel->setText(listName);
}

// Function sets the current list ID
void TaskWidget::setCurrentListId(int listId) {
    currentListId = listId;
}

// Function returns the current list ID
int TaskWidget::getCurrentListId() const {
    return currentListId;
}



// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_taskwidget.cpp"
