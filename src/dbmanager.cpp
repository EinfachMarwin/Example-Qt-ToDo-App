//
// Created by Marwin Nowak on 21.11.23.
//


#include "dbmanager.h"

using Orm::DB;

using ConfigUtils = Orm::Utils::Configuration;

using namespace Orm::Constants; // NOLINT(google-build-using-namespace)

DatabaseManager::DatabaseManager(const QString &databasePath)
{
    // Create a database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    if (!db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    auto manager = DB::create({
        {"driver",                  "QSQLITE"},
        {"database",                databasePath},
        {"foreign_key_constraints", true},
        {"check_database_exists",   true},
        {"qt_timezone",             QVariant::fromValue(Qt::UTC)},
        {"return_qdatetime",        true},
        {"prefix",                  ""},
        {"prefix_indexes",          false},
    });
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen())
    {
        db.close();
        qDebug() << "Database: connection closed";
    } else
    {
        qDebug() << "Database: connection already closed";
    }
}