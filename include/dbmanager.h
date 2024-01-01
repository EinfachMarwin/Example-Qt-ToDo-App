//
// Created by Marwin Nowak on 21.11.23.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <memory>

#include <orm/db.hpp>
#include <orm/utils/configuration.hpp>

class DatabaseManager
{
public:
    DatabaseManager(const QString &databasePath);
    ~DatabaseManager();

private:
    std::shared_ptr<Orm::DatabaseManager> manager;
    QSqlDatabase db;
};

#endif //DBMANAGER_H
