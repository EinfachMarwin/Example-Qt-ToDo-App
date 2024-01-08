//
// Created by Marwin Nowak on 18.11.23.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QApplication>

#include <QDesktopServices>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

public slots:
    static void onSettingsButtonClicked();
    static void onHelpButtonClicked();
    static void onTasksButtonClicked();
};

#endif // MAINWINDOW_H
