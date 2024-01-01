//
// Created by Marwin Nowak on 02.12.2023.
//

#ifndef TASK_H
#define TASK_H

#include <orm/tiny/model.hpp>
#include <QString>

using Orm::Tiny::Model;

class Task final : public Model<Task>
{
    friend Model;

    using Model::Model;

private:

public:
};

#endif //TASK_H