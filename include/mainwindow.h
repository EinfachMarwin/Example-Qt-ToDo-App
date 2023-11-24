//
// Created by Marwin Nowak on 18.11.23.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QObject>
#include <QDebug>
#include <QDesktopServices>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    static void onSettingsButtonClicked();
    static void onHelpButtonClicked();
    static void onTasksButtonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
