//
// Created by Marwin Nowak on 26.11.23.
//

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
    ~TaskWidget() override;

    QWidget* showTasksForListId1();
    void setListName(const QString& listName);
    void refreshTaskList();

    public slots:
        void returnPressed();

private:
    QWidget* createHeaderWidget();
    QWidget* createTaskWidget(const Task& task);

    QLineEdit *addTaskLineEdit;
    QListWidget *taskListWidget;
    QLabel* headerLabel;
};

#endif // TASKWIDGET_H