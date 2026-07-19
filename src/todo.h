#pragma once

#include "domain_error.h"

#include <expected>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>

enum class Priority
{
    high, medium, low
};

class Todo
{
    int id_ {};
    std::string title_ {};
    bool completed_ {false};
    std::vector<std::string> tags_ {};
    std::chrono::system_clock::time_point created_at_{};
    Priority priority_ {Priority::medium};
public:
    const std::string& get_title() const;
    std::expected<void, DomainError> set_title(std::string_view t);
    int get_id() const;
    bool is_completed() const;
    void set_completed(bool done);
    const std::vector<std::string>& get_tags() const;
    Priority get_priority() const;
    void set_priority(Priority p);
    explicit Todo(int id, std::string title);
};
