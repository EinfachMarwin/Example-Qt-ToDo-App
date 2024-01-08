#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>

#include "taskwidget.h"

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget* parent = nullptr);
    ~ListWidget() override;

    public slots:
        void onAddButtonClicked();
        void onDeleteListButtonClicked(int listId);
        void onInboxButtonClicked();
        void onTodayButtonClicked();
        void setTaskWidget(TaskWidget* widget);
        TaskWidget* getTaskWidget() const;

private:
    TaskWidget* taskWidget;
    QWidget* createHeaderWidget();
    QWidget* createMenuWidget();
    QPushButton* createMenuButton(const QString& buttonName, const QString& iconPath, QLayout* parent);
    void refreshListWidget();

private:
    QVBoxLayout* menuLayout;
    QVBoxLayout* listLayout;
};

#endif //LISTWIDGET_H