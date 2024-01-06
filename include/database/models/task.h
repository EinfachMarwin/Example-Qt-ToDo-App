//
// Created by Marwin Nowak on 02.12.2023.
//

#ifndef TASK_H
#define TASK_H

#include <orm/tiny/model.hpp>
#include <orm/db.hpp>
#include <QVariant>

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
    bool is_done;
    std::string deadline;

    static void createTable()
    {
        DB::statement("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, list_id INTEGER, is_done BOOLEAN, deadline TEXT)");
    }

    void save()
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            QVector<QVariant> values = {QString::fromStdString(description), list_id, is_done, QString::fromStdString(deadline)};
            DB::statement("INSERT INTO tasks (description, list_id, is_done, deadline) VALUES (?, ?, ?, ?)", values);

            // Commit the transaction
            DB::commit();
        } catch (...) {
            // An error occurred, rollback the transaction
            DB::rollBack();
            throw;  // Re-throw the exception
        }
    }

    static void deleteTask(int taskId)
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            QVector<QVariant> values = {taskId};
            DB::statement("DELETE FROM tasks WHERE id = ?", values);

            // Commit the transaction
            DB::commit();
        } catch (...) {
            // An error occurred, rollback the transaction
            DB::rollBack();
            throw;  // Re-throw the exception
        }
    }



    static QVector<Task> getTasksByListId(int listId)
    {
        QVector<QVariant> values = {listId};
        QSqlQuery result = DB::select("SELECT * FROM tasks WHERE list_id = ?", values);

        QVector<Task> tasks;
        while (result.next()) {
            Task task;
            task.id = result.value("id").toInt();
            task.description = result.value("description").toString().toStdString();
            task.list_id = result.value("list_id").toInt();
            task.is_done = result.value("is_done").toBool();
            task.deadline = result.value("deadline").toString().toStdString();
            tasks.push_back(task);
        }

        return tasks;
    }

    static void updateTaskStatus(int taskId, bool isDone)
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            QVector<QVariant> values = {isDone, taskId};
            DB::statement("UPDATE tasks SET is_done = ? WHERE id = ?", values);

            // Commit the transaction
            DB::commit();
        } catch (...) {
            // An error occurred, rollback the transaction
            DB::rollBack();
            throw;  // Re-throw the exception
        }
    }

    static void updateTaskDeadline(int taskId, const std::string& deadline)
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            QVector<QVariant> values = {QString::fromStdString(deadline), taskId};
            DB::statement("UPDATE tasks SET deadline = ? WHERE id = ?", values);

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