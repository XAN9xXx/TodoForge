#pragma once

#include <expected>
#include <string>
#include <vector>

#include "domain_error.h"
#include "todo.h"

class TodoCollection
{
    std::vector<Todo> todos_ {};
    int next_id_ {1};
public:
    Todo& add(std::string title);
    Todo* find_by_id(int id);
    std::expected<void, DomainError> remove(int id);
    const std::vector<Todo>& all() const;
    void insert(Todo todo);
};
