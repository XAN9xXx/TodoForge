#include "todo.h"

#include <string>
#include <string_view>
#include <vector>

namespace {
    bool is_blank(std::string_view s)
    {
        return s.empty() || s.find_first_not_of(" \t\n\r") == std::string_view::npos;
    }
}

const std::string& Todo::get_title() const
{
    return title_;
}

void Todo::set_title(std::string_view t)
{
    if (is_blank(t)) return;
    title_ = t;
}

int Todo::get_id() const
{
    return id_;
}

bool Todo::is_completed() const
{
    return completed_;
}

void Todo::set_completed(bool done)
{
    completed_ = done;
}

const std::vector<std::string>& Todo::get_tags() const
{
    return tags_;
}

Priority Todo::get_priority() const
{
    return priority_;
}

void Todo::set_priority(Priority p)
{
    priority_ = p;
}

Todo::Todo(int id, std::string title): id_{id}, title_{std::move(title)} {}
