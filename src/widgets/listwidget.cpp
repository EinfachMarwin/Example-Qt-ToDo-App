//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/listwidget.h"

#include <QVBoxLayout>

ListWidget::ListWidget(QWidget *parent) : QWidget(parent) {
    // Create main Widget
    auto *mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #283655;");
    mainWidget->setMinimumSize(QSize(250, 600));

    // Create main layout
    auto *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    parent->layout()->addWidget(mainWidget);
}

ListWidget::~ListWidget() {

}


// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_listwidget.cpp"