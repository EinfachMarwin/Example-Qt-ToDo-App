//
// Created by Marwin Nowak on 02.12.2023.
//

#ifndef TASK_H
#define TASK_H

#include <orm/tiny/model.hpp>
#include <orm/db.hpp>
#include <qdebug.h>

using Orm::DB;
using Orm::Tiny::Model;

class Task : public Model<Task>
{
public:
    // Define table name
    static constexpr auto table = "tasks";

    // Define fields
    int id;
    std::string description;
    int list_id;

    static void createTable()
    {
        DB::statement("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, list_id INTEGER)");
    }

    void save()
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            QVector<QVariant> values = {QString::fromStdString(description), list_id};
            DB::statement("INSERT INTO tasks (description, list_id) VALUES (?, ?)", values);

            // Commit the transaction
            DB::commit();
        } catch (...) {
            // An error occurred, rollback the transaction
            DB::rollBack();
            throw;  // Re-throw the exception
        }
    }
};
#endif //TASK_H