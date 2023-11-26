//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>

class ListWidget : public QWidget {
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget() override;
};

#endif //LISTWIDGET_H
