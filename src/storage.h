#pragma once

#include "storage_error.h"
#include "todo_collection.h"

#include <expected>
#include <string>

std::expected<void, StorageError> save(const TodoCollection& todos, const std::string& filepath);
std::expected<TodoCollection, StorageError>  load(const std::string& filepath);
