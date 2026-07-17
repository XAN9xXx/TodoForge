#include <charconv>
#include <iostream>
#include <string>
#include <system_error>
#include <unordered_map>
#include <string_view>
#include <optional>

enum class Command
{
    help, version, add, list, done, remove, unknown
};

struct Todo
{
    int id;
    std::string title;
    std::string created_date;
    bool completed;
};

std::string help();
std::string version();
std::string unknown();
std::string handle_add(std::string_view text);
std::string handle_list();
std::string handle_done(int id);
std::string handle_remove(int id);
std::string write_todos();
std::string read_todos();
[[nodiscard]]
std::optional<int> parse_id(std::string_view str);
Command parse_command(const std::string& str);

int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        std::cout << help();
        return 0;
    }
    switch (parse_command(argv[1])) 
    {
        case Command::help :
            std::cout << help();
            break;
        case Command::version :
            std::cout << version();
            break;
        case Command::add :
            if (argc <= 2)
            {
                std::cerr << "Error: 'add' requires a title!\n";
                return 1;
            }
            std::cout << handle_add(argv[2]);
            break;
        case Command::list :
            std::cout << handle_list();
            break;
        case Command::done : {
            if (argc <= 2)
            {
                std::cerr << "Error: 'done' requires a ID!\n";
                return 1;
            }
            auto maybe_id = parse_id(argv[2]);
            if (!maybe_id) {
                std::cerr << "Error: invalid ID\n";
                return 1;
            }
            std::cout << handle_done(*maybe_id);
            break;
            }
        case Command::remove : {
            if (argc <= 2)
            {
                std::cerr << "Error: 'remove' requires a ID!\n";
                return 1;
            }
            auto maybe_id = parse_id(argv[2]);
            if (!maybe_id) {
                std::cerr << "Error: invalid ID\n";
                return 1;
            }
            std::cout << handle_remove(*maybe_id);
            break;
        }
        case Command::unknown :
            std::cerr << unknown();
            return 1;
    }
    return 0;
}

Command parse_command(const std::string& str)
{
    static const std::unordered_map <std::string, Command> map =
    {
        {"help", Command::help},
        {"-h", Command::help},
        {"--help", Command::help},
        {"version", Command::version},
        {"-v", Command::version},
        {"--version", Command::version},
        {"add", Command::add},
        {"list", Command::list},
        {"done", Command::done},
        {"remove", Command::remove}
    };
    auto it = map.find(str);
    return (it != map.end()) ? it -> second : Command::unknown;
}

std::optional<int> parse_id(std::string_view str)
{
    int id{};
    const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), id);
    if (ec == std::errc{})
    {
        if (id <= 0) return std::nullopt;
        if (ptr != str.data() + str.size()) return std::nullopt;
        return id;
    }
    return std::nullopt;
}

std::string help()
{
    std::string help_text = "TodoForge 0.1.0\nA simple command-line todo tool\n\nUsage:\n  todo <command> [arguments]\n  todo [option]\n\nCommands:\n  add <title>    Create a new todo\n  list           Show all todos\n  done <id>      Mark a todo as completed\n  remove <id>    Remove a todo\n  help           Show this help message\n\nOptions:\n  -h, --help     Show this help message\n  -v, --version  Show version information\n\nExamples:\n  todo add \"write README\"\n  todo list\n  todo done 1\n  todo remove 1\n";
    return help_text; 
}
std::string version()
{
    return "TodoForge 0.1.0\n";
}
std::string unknown()
{
    return "Unknown command, please check help\n";
}
std::string handle_add(std::string_view text)
{
   return "add command\n"; 
}
std::string handle_list()
{
    return "list command\n";
}
std::string handle_done(int id)
{
    return "done command\n";
}
std::string handle_remove(int id)
{
    return "remove command\n";
}
