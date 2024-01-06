#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget* parent = nullptr);
    ~ListWidget() override;

    public slots:
    static void onTodayButtonClicked();
    static void onImportantButtonClicked();
    static void onInboxButtonClicked();
    void onAddButtonClicked();
    void onDeleteListButtonClicked(int listId);

private:
    QWidget* createHeaderWidget();
    QWidget* createMenuWidget();private:
    QVBoxLayout* menuLayout;
    QVBoxLayout* listLayout;

    QPushButton* createMenuButton(const QString& buttonName, const QString& iconPath, QLayout* parent);
    void refreshListWidget();
};

#endif //LISTWIDGET_H