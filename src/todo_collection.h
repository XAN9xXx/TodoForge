#pragma once

#include <string>
#include <vector>

#include "todo.h"

class TodoCollection
{
    std::vector<Todo> todos_ {};
    int next_id_ {1};
public:
    Todo& add(std::string title);
    Todo* find_by_id(int id);
    bool remove(int id);
    const std::vector<Todo>& all() const;
};
