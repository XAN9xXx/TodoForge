#pragma once

#include "todo_collection.h"

#include <string>
#include <string_view>

std::string handle_add(TodoCollection& todos, std::string_view title);
std::string handle_list(const TodoCollection& todos);
std::string handle_done(TodoCollection& todos, int id);
std::string handle_remove(TodoCollection& todos, int id);
std::string write_todos();
std::string read_todos();
