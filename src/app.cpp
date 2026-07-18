#include "app.h"
#include "todo_collection.h"
#include "todo.h"

#include <string>
#include <string_view>

std::string handle_add(TodoCollection& todos, std::string_view title)
{
    Todo& new_todo {todos.add(std::string {title})};
    return "Added task #" + std::to_string(new_todo.get_id()) + ": " + new_todo.get_title() + ".\n" ;
}

std::string handle_list(const TodoCollection& todos)
{
    std::string result {};
    for (const auto& todo : todos.all())
    {
        result += std::to_string(todo.get_id()) + ": " + todo.get_title() + ".\n";
    }
    if (result.empty()) return "No tasks now.\n";
    return result;
}

std::string handle_done(TodoCollection& todos, int id)
{
    if (auto* todo = todos.find_by_id(id))
    {
        if (todo -> is_completed()) return "Task #" + std::to_string(id) + " is already done.\n";
        todo -> set_completed(true);
        return "Marked task #" + std::to_string(id) + " as done.\n";
    }
    return "Error: task #" + std::to_string(id) + " not found.\n";
}

std::string handle_remove(TodoCollection& todos, int id)
{
    if (auto* todo = todos.find_by_id(id))
    {
        todos.remove(id);
        return "Removed task #" + std::to_string(id) + ".\n";
    }
    return "Error: task #" + std::to_string(id) + " not found.\n";
}
