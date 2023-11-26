//
// Created by Marwin Nowak on 18.11.23.
//

#include "windows/mainwindow.h"
#include "dbmanager.h"

// Function initializes the Application
int main(int argc, char* argv[]) {
    // Create the application
    QApplication app(argc, argv);
    // Create the main window
    MainWindow w;
    w.show();

    // Set the application icon
    QApplication::setWindowIcon(QIcon("../res/images/LogoToDoAppTransparent.png"));

    // Create a database manager
    DbManager dbManager("../ToDoApp.db");

    return app.exec();
}