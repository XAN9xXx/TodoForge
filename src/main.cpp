#include "app.h"
#include "cli.h"
#include "todo_collection.h"

#include <iostream>

int main(int argc, char* argv[])
{
    TodoCollection todos {};

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
                std::cerr << "Error: 'add' requires a title!" << std::endl;
                return 1;
            }
            std::cout << handle_add(todos, argv[2]);
            break;
        case Command::list :
            std::cout << handle_list(todos);
            break;
        case Command::done : {
            if (argc <= 2)
            {
                std::cerr << "Error: 'done' requires a ID!" << std::endl;
                return 1;
            }
            auto maybe_id = parse_id(argv[2]);
            if (!maybe_id) {
                std::cerr << "Error: invalid ID" << std::endl;
                return 1;
            }
            std::cout << handle_done(todos, *maybe_id);
            break;
            }
        case Command::remove : {
            if (argc <= 2)
            {
                std::cerr << "Error: 'remove' requires a ID!" << std::endl;
                return 1;
            }
            auto maybe_id = parse_id(argv[2]);
            if (!maybe_id) {
                std::cerr << "Error: invalid ID" << std::endl;
                return 1;
            }
            std::cout << handle_remove(todos, *maybe_id);
            break;
        }
        case Command::unknown :
            std::cerr << unknown();
            return 1;
    }
    return 0;
}

