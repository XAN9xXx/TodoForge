# TodoForge

A **local-first task workflow engine** built from scratch with C++23 — not a plain todo list, but a pipeline from task modeling through persistence, query expressions, dependency graphs, event sourcing, and recurrence planning.

## Build

```bash
cmake --preset debug
cmake --build --preset debug
```

Requires CMake 3.25+, Ninja, and GCC with C++23 support. Release builds: `--preset release`.

## Usage

```bash
todo help                 # help text
todo version              # version info

todo add "write README"   # create a task
todo list                 # list all tasks
todo done 1               # mark task 1 as done
todo remove 1             # delete task 1
```

