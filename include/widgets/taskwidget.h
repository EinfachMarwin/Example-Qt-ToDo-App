#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include "database/models/task.h"

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(QWidget* parent = nullptr);
    ~TaskWidget();

    void updateTaskList(const QVector<Task>& tasks);
    void refreshTaskList(int listId);
    void showTasksForToday();
    QWidget* showTasksForListId(int listId);
    void setListName(const QString& listName);

    void setCurrentListId(int listId);
    int getCurrentListId() const;

    public slots:
        void returnPressed();

private:
    QWidget* createHeaderWidget();
    QWidget* createTaskWidget(const Task& task);

    QLineEdit *addTaskLineEdit;
    QListWidget *taskListWidget;
    QLabel* headerLabel;

    int currentListId;
};

#endif // TASKWIDGET_H