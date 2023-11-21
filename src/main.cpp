//
// Created by Marwin Nowak on 18.11.23.
//

#include <QApplication>
#include "../include/mainwindow.h"
#include "../include/dbmanager.h"

// Function instantiating the main window
int main(int argc, char* argv[]) {
    // Create the application
    QApplication app(argc, argv);
    // Create the main window
    MainWindow w;
    w.show();

    // Create a database manager
    DbManager dbManager("todo.db");

    return app.exec();
}
