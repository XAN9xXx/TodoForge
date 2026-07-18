#include "todo_collection.h"

#include <algorithm>

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

bool TodoCollection::remove(int id)
{
    auto it = std::find_if(todos_.begin(), todos_.end(),
        [id](const Todo& todo) { return todo.get_id() == id; });

    if (it != todos_.end())
    {
        todos_.erase(it);
        return true;
    }
    return false;
}

const std::vector<Todo>& TodoCollection::all() const
{
    return todos_;
}
