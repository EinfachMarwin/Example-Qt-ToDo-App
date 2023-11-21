//
// Created by Marwin Nowak on 18.11.23.
//

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../include/dbmanager.h"

// Constructor for the main window
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // Setup the main window
    ui->setupUi(this);
    resize(1200, 800);
    setWindowTitle("ToDo List");

    // TODO: Implement the UI for the MainWindow.

}

// Destructor for the main window
MainWindow::~MainWindow() {
    delete ui;
}

// IMPORTANT: Do not delete the following line; otherwise, the program will crash.
#include "moc_mainwindow.cpp"