//
// Created by Marwin Nowak on 02.12.2023.
//

#ifndef LIST_H
#define LIST_H

#include <orm/tiny/model.hpp>
#include <QString>

using Orm::Tiny::Model;

class List final : public Model<List>
{
    friend Model;

    using Model::Model;

private:
    QString name;
    int main_list_id;

public:
    // Getter für name
    QString getName() const { return name; }

    // Setter für name
    void setName(const QString &value) { name = value; }

    // Getter für main_list_id
    int getMainListId() const { return main_list_id; }

    // Setter für main_list_id
    void setMainListId(int value) { main_list_id = value; }
};

#endif //LIST_H