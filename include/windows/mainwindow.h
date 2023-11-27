//
// Created by Marwin Nowak on 18.11.23.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QPixmap>
#include <QIcon>
#include <QApplication>
#include <QSplitter>

#include <QDesktopServices>

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
};

#endif // MAINWINDOW_H
