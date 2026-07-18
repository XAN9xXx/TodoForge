#pragma once

#include <optional>
#include <string>
#include <string_view>

enum class Command
{
    help, version, add, list, done, remove, unknown
};

[[nodiscard]]
std::optional<int> parse_id(std::string_view str);
Command parse_command(const std::string& str);
std::string help();
std::string version();
std::string unknown();
