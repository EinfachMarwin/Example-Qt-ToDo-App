//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

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

    QWidget* showTasksForListId1(); // Updated return type to QWidget*

    public slots:
        void returnPressed(); // Corrected the spelling

private:
    QWidget* createHeaderWidget();
    QWidget* createTaskWidget(const Task& task);

    QLineEdit *addTaskLineEdit;
    QListWidget *taskListWidget; // Assuming you want to use this for task display
};

#endif // TASKWIDGET_H
