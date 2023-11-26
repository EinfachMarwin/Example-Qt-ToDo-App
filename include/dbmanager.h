//
// Created by Marwin Nowak on 21.11.23.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QSqlDatabase>


// Class for managing the database
class DbManager {
public:
    explicit DbManager(const QString& path);
    ~DbManager();

private:
    QSqlDatabase db;
};

#endif //DBMANAGER_H
