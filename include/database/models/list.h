//
// Created by Marwin Nowak on 02.12.2023.
//

#ifndef LIST_H
#define LIST_H

#include <orm/tiny/model.hpp>
#include <orm/db.hpp>

using Orm::DB;
using Orm::Tiny::Model;

class List : public Model<List>
{
public:
    // Define table name
    static constexpr auto table = "listen";

    // Define fields
    int id;
    std::string name;

    static void createTable()
    {
        DB::statement("CREATE TABLE IF NOT EXISTS listen (id INTEGER PRIMARY KEY, name TEXT)");
    }

    void save()
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            QVector<QVariant> values = {QString::fromStdString(name)};
            DB::statement("INSERT INTO listen (name) VALUES (?)", values);

            // Commit the transaction
            DB::commit();
        } catch (...) {
            // An error occurred, rollback the transaction
            DB::rollBack();
            throw;  // Re-throw the exception
        }
    }
};

#endif //LIST_H