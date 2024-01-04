//
// Created by Marwin Nowak on 18.11.23.
//

#include "windows/mainwindow.h"
#include "dbmanager.h"

#include <sqlite3.h>
#include <database/models/task.h>
#include <database/models/list.h>

// Function initializes the Application
int main(int argc, char* argv[])
{
    qDebug() << "SQLite3 version" << sqlite3_libversion();

    // Create the application
    QApplication app(argc, argv);

    // Set the application icon
    QApplication::setWindowIcon(QIcon(":res/images/LogoToDoAppTransparent.png"));

    // Create a database manager
    DatabaseManager dbManager("../database.db");

    // Create tables
    List::createTable();
    Task::createTable();

    // Create the main window
    MainWindow w;
    w.show();

    return app.exec();
}