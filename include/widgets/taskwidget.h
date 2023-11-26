//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>

class TaskWidget : public QWidget {
    Q_OBJECT

public:
    explicit TaskWidget(QWidget *parent = nullptr);
    ~TaskWidget() override;
};






#endif //TASKWIDGET_H
