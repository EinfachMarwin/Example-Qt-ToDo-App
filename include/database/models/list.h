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

    static int getInboxId()
    {
        QSqlQuery result = DB::select("SELECT id FROM listen WHERE name = 'Inbox'");
        if (result.next()) {
            return result.value("id").toInt();
        }
        return -1;  // Return -1 if the Inbox list does not exist
    }

    static void createTable()
    {
        DB::statement("CREATE TABLE IF NOT EXISTS listen (id INTEGER PRIMARY KEY, name TEXT)");
        createDefaultInbox();
    }

    static void createDefaultInbox()
    {
        QSqlQuery result = DB::select("SELECT * FROM listen WHERE name = 'Inbox'");

        if (!result.next()) {
            List inbox;
            inbox.name = "Inbox";
            inbox.save();
        }
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

    static void deleteList(int listId)
    {
        // Start a new transaction
        DB::beginTransaction();

        try {
            // Get the ID of the Inbox list
            int inboxId = getInboxId();
            if (inboxId == -1) {
                throw std::runtime_error("Inbox list does not exist");
            }

            // Move all tasks from the list to be deleted to the Inbox list
            QVector<QVariant> moveValues = {inboxId, listId};
            DB::statement("UPDATE tasks SET list_id = ? WHERE list_id = ?", moveValues);

            // Delete the list
            QVector<QVariant> deleteValues = {listId};
            DB::statement("DELETE FROM listen WHERE id = ?", deleteValues);

            // Commit the transaction
            DB::commit();
        } catch (...) {
            // An error occurred, rollback the transaction
            DB::rollBack();
            throw;  // Re-throw the exception
        }
    }

    static bool nameExists(const std::string& name)
    {
        QSqlQuery result = DB::select("SELECT * FROM listen WHERE name = ?", {QString::fromStdString(name)});
        return result.next();
    }

    static QVector<List> getAllLists()
    {
        QSqlQuery result = DB::select("SELECT * FROM listen");

        QVector<List> lists;
        while (result.next()) {
            List list;
            list.id = result.value("id").toInt();
            list.name = result.value("name").toString().toStdString();
            lists.push_back(list);
        }

        return lists;
    }
};

#endif //LIST_H