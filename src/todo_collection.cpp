#include "todo_collection.h"
#include "domain_error.h"

#include <algorithm>
#include <expected>

Todo& TodoCollection::add(std::string title)
{
    todos_.emplace_back(next_id_, std::move(title));
    next_id_++;
    return todos_.back();
}

Todo* TodoCollection::find_by_id(int id)
{
    auto it = std::find_if(todos_.begin(), todos_.end(),
        [id](const Todo& todo) { return todo.get_id() == id; });

    if (it != todos_.end()) return &(*it);
    return nullptr;
}

std::expected<void, DomainError> TodoCollection::remove(int id)
{
    auto it = std::find_if(todos_.begin(), todos_.end(),
        [id](const Todo& todo) { return todo.get_id() == id; });

    if (it != todos_.end())
    {
        todos_.erase(it);
        return {};
    }
    return std::unexpected{DomainError::task_not_found};
}

const std::vector<Todo>& TodoCollection::all() const
{
    return todos_;
}

void TodoCollection::insert(Todo todo)
{
    todos_.push_back(std::move(todo));
    if (todos_.back().get_id() >= next_id_)
    {
        next_id_ = todos_.back().get_id() + 1;
    }
}
