#include <iostream>
#include <string>
#include <unordered_map>

enum class Command
{
    help, version, add, list, done, remove, unknown
};

std::string help();
std::string version();
std::string unknown();
std::string handle_add();
std::string handle_list();
std::string handle_done();
std::string handle_remove();
std::string normalize_command(std::string& user_input_command);
Command parse_command(const std::string& str);

int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        std::cout << help();
        return 0;
    }
    std::string user_command_text = argv[1];
    std::string sys_command_text = normalize_command(user_command_text);
    switch (parse_command(sys_command_text)) 
    {
        case Command::help :
            std::cout<<help();
            break;
        case Command::version :
            std::cout<<version();
            break;
        case Command::add :
            std::cout<<handle_add();
            break;
        case Command::list :
            std::cout<<handle_list();
            break;
        case Command::done :
            std::cout<<handle_done();
            break;
        case Command::remove :
            std::cout<<handle_remove();
            break;
        case Command::unknown :
            std::cout<<unknown();
            break;
    }

    return 0;
}

Command parse_command(const std::string& str)
{
    static const std::unordered_map<std::string, Command> map =
    {
        {"help", Command::help},
        {"version", Command::version},
        {"add", Command::add},
        {"list", Command::list},
        {"done", Command::done},
        {"remove", Command::remove}
    };
    auto it = map.find(str);
    return (it != map.end()) ? it -> second : Command::unknown;
}

std::string normalize_command(std::string& user_input_command)
{
    std::string output_command;
    if(user_input_command == "-v" || user_input_command == "--version")
    {
        output_command = "version";
        return output_command;
    }
    if(user_input_command == "-h"|| user_input_command == "--help" || user_input_command == "help")
    {
        output_command = "help";
        return output_command;
    }

    if(user_input_command == "add") return user_input_command;
    if(user_input_command == "list") return user_input_command;
    if(user_input_command == "done") return user_input_command;
    if(user_input_command == "remove") return user_input_command;
    return "unknown";
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
    return "Unknown command,please check help\n";
}
std::string handle_add()
{
    return "add command\n";
}
std::string handle_list()
{
    return "list command\n";
}
std::string handle_done()
{
    return "done command\n";
}
std::string handle_remove()
{
    return "remove command\n";
}
