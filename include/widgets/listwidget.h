//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class ListWidget : public QWidget {
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget() override;

public slots:
    static void onTodayButtonClicked();
    static void onImportantButtonClicked();
    static void onInboxButtonClicked();

private:
    QWidget* createHeaderWidget();
    QWidget* createMenuWidget();

    QPushButton* createMenuButton(const QString& buttonName, const QString& iconPath, QLayout* parent);
};

#endif //LISTWIDGET_H
