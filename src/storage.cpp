#include "storage.h"
#include "storage_error.h"
#include "todo.h"
#include "todo_collection.h"

#include <algorithm>
#include <charconv>
#include <chrono>
#include <expected>
#include <filesystem>
#include <fstream>
#include <ios>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace 
{
    template<typename T>
    bool parse_field(std::string_view sv, T& out)
    {
        auto [ptr, ec] {std::from_chars(sv.data(), sv.data() + sv.size(), out)};
        return ec == std::errc{} && ptr == sv.data() + sv.size();
    }

    std::expected<Todo, StorageError> parse_todo_line(const std::string_view& line)
    {
        std::vector<std::string_view> result {};
        size_t start {0};
        size_t end {line.find(':')};
        while (end != std::string::npos)
        {
            result.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(':', start);
        }
        result.push_back(line.substr(start));

        int id {};
        if (!parse_field(result[0], id))
            return std::unexpected{StorageError::invalid_format};

        bool completed {result[2] == "1"};
        if (result[2] != "0" && result[2] != "1")
            return std::unexpected{StorageError::invalid_format};

        std::vector<std::string> tags {};
        std::istringstream iss(std::string{result[3]});
        std::string token {};
        while (std::getline(iss, token, ','))
            tags.push_back(token);

        long long ts {};
        if (!parse_field(result[4], ts))
            return std::unexpected{StorageError::invalid_format};
        auto created_at = std::chrono::system_clock::time_point{std::chrono::microseconds{ts}};

        int pri {};
        if (!parse_field(result[5], pri))
            return std::unexpected{StorageError::invalid_format};
        if (pri < 0 || pri > 2)
            return std::unexpected{StorageError::invalid_format};
        Priority priority {static_cast<Priority>(pri)};

        Todo todo {id, std::string{result[1]}, created_at};
        todo.set_completed(completed);
        todo.set_tags(tags);
        todo.set_priority(priority);
        return todo;
    }
}

std::expected<void, StorageError> save(const TodoCollection& todos, const std::string& filepath)
{
    std::ofstream file {filepath};
    if (!file.is_open())
        return std::unexpected{StorageError::write_failed};
    file << "V1" << std::endl;
    for (const auto& todo : todos.all())
    {
        std::string line {};
        line += std::to_string(todo.get_id()) + ':';
        line += todo.get_title() + ':';
        line += std::string(todo.is_completed() ? "1" : "0") + ':';
        bool first {true};
        for (const auto& tag : todo.get_tags())
        {
            if (!first)
                line += ',';
            line += tag;
            first = false;
        }
        auto ts = todo.get_created_at().time_since_epoch().count();
        line += ':' + std::to_string(ts) + ':';
        line += std::to_string(static_cast<int>(todo.get_priority()));
        file << line << std::endl;
        if (!file.good())
            return std::unexpected{StorageError::write_failed};
    }
    return {}; // TODO: atomic write
}

std::expected<TodoCollection, StorageError>  load(const std::string& filepath)
{
    if (!std::filesystem::exists(filepath))
        return TodoCollection {};

    TodoCollection todos {};
    std::ifstream file {filepath};
    if (!file.is_open())
        return std::unexpected{StorageError::cannot_open};
    std::string line {};
    std::getline(file, line);
    if (line != "V1")
        return std::unexpected{StorageError::invalid_format};

    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        auto maybe_todo {parse_todo_line(line)};
        if (!maybe_todo)
            return std::unexpected{maybe_todo.error()};
        todos.insert(std::move(*maybe_todo));
    }
    return todos;
}
