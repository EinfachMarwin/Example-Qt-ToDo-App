//
// Created by Marwin Nowak on 21.11.23.
//

#include "dbmanager.h"

// Constructor for the database manager
DbManager::DbManager(const QString&) {
    // Create a connection to the database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("todo.db");

    // Check if the database is open
    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    }
    else {
        qDebug() << "Database: connection successfull";
    }
}

// Close the database connection
DbManager::~DbManager() {
    // Check if the database is open
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database: connection closed successfully";
    }
    else {
        qDebug() << "Error: connection with database already closed";
    }
}

// TODO: Design and document the database schema with an ERD.
// TODO: Create all tables in separate functions.
// TODO: Implement a function to initialize all tables. Error handling is required.

