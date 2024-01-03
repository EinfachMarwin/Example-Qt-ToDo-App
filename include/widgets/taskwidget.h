//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <qdebug.h>
#include <QListWidget>

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(QWidget* parent = nullptr);
    ~TaskWidget() override;

public slots:
    void retunPressed();

private:
    QWidget* createHeaderWidget();
    void loadTasks();

    QLineEdit *addTaskLineEdit;
    QListWidget *taskListWidget;
};


#endif //TASKWIDGET_H
