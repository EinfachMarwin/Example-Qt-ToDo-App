//
// Created by Marwin Nowak on 26.11.23.
//

#include "widgets/taskwidget.h"

#include <QLabel>
#include <QVBoxLayout>


TaskWidget::TaskWidget(QWidget *parent) : QWidget(parent) {
    auto *mainWidget = new QWidget(this);
    mainWidget->setStyleSheet("background-color: #ffffff;");
    mainWidget->setMinimumSize(QSize(250, 600));

    auto *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(createHeaderWidget());
    mainLayout->addStretch();

    parent->layout()->addWidget(mainWidget);
}

TaskWidget::~TaskWidget() {

}

QWidget* TaskWidget::createHeaderWidget() {
    // Create a header widget
    auto *headerWidget = new QWidget(this);
    headerWidget->setFixedHeight(250);


    // Create a layout for the header widget
    auto *headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setContentsMargins(5, 0, 0, 0);
    headerLayout->setAlignment(Qt::AlignTop);
    headerLayout->setContentsMargins(10, 10, 10, 10);

    // Create a label for the header widget
    auto *headerLabel = new QLabel(headerWidget);
    headerLabel->setText("<LISTNAME HERE>");
    headerLabel->setStyleSheet("color: #1e1f26; font-size: 20px; font-weight: bold;");
    headerLayout->addWidget(headerLabel);

    // Create line edit to add new tasks
    auto *addTaskLineEdit = new QLineEdit(this);
    addTaskLineEdit->setStyleSheet("background-color: #d0e1f9; color: #283655; font-size: 16px; border-radius: 5px;");
    addTaskLineEdit->setContentsMargins(4, 4, 4, 4);
    addTaskLineEdit->setPlaceholderText("Add a new task... press enter to save");
    addTaskLineEdit->setFixedHeight(40);
    headerLayout->addSpacing(1);
    headerLayout->addWidget(addTaskLineEdit);

    // Connect the returnPressed signal to the addTask slot
    connect(addTaskLineEdit, &QLineEdit::returnPressed, this, &TaskWidget::retunPressed);

    return headerWidget;
}

void TaskWidget::retunPressed() {
    qDebug() << "Return pressed";
}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "widgets/moc_taskwidget.cpp"
