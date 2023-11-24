//
// Created by Marwin Nowak on 18.11.23.
//

#include <QApplication>
#include <QIcon>
#include "../include/mainwindow.h"
#include "../include/dbmanager.h"

// Function initializes the Application
int main(int argc, char* argv[]) {
    // Create the application
    QApplication app(argc, argv);
    // Create the main window
    MainWindow w;
    w.show();

    // Set the application icon
    app.setWindowIcon(QIcon("../res/images/LogoToDoAppTransparent.png"));

    // Create a database manager
    DbManager dbManager("todo.db");

    return app.exec();
}
