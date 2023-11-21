//
// Created by Marwin Nowak on 21.11.23.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>

// Class for managing the database
class DbManager {
public:
    explicit DbManager(const QString &);
    ~DbManager();

    // Create all tables
    bool createTable();

private:
    QSqlDatabase db;

    // Create the tables
    bool createTasksTable();
    bool createSubTasksTable();
    bool createListsTable();
    bool createTagsTable();
    bool createPriorityTable();
    bool createDatesTable();

};

#endif //DBMANAGER_H
