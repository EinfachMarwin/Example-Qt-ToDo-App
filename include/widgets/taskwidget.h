//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>

class TaskWidget : public QWidget {
    Q_OBJECT

public:
    explicit TaskWidget(QWidget *parent = nullptr);
    ~TaskWidget() override;

public slots:
    static void retunPressed();
private:
    QWidget* createHeaderWidget();
};






#endif //TASKWIDGET_H
