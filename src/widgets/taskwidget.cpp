//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/taskwidget.h"

#include <QVBoxLayout>


TaskWidget::TaskWidget(QWidget *parent) : QWidget(parent) {
    auto *mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #d0e1f9;");
    mainWidget->setMinimumSize(QSize(250, 600));

    auto *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    parent->layout()->addWidget(mainWidget);
}

TaskWidget::~TaskWidget() {

}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_taskwidget.cpp"
