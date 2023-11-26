 //
// Created by Marwin Nowak on 21.11.23.
//

#include "dbmanager.h"

// Constructor for the database manager
DbManager::DbManager(const QString&path) {
    // Create a connection to the database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    // Check if the database is open
    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    }
    else {
        qDebug() << "Database: connection established successfully";
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