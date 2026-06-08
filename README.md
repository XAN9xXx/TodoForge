# TodoForge

TodoForge is a simple command-line todo tool written in C++.

This is primarily a practice project rather than an attempt to build a feature-rich todo application. The goal is straightforward: start with a minimal CLI skeleton and incrementally build it up while practicing C++, Vim, Git workflows, and project structuring.

The name "Forge" reflects this gradual process of shaping a small tool into form.

> And yes, it reminds me a little of Minecraft, lol.

## Current Status & Roadmap

TodoForge is in a very early stage. It is currently a CLI skeleton that can parse commands, but the core features are still placeholders awaiting implementation.

**CLI Engine (Implemented)**

- [x] Program entry point
- [x] `argc` / `argv` argument inspection
- [x] Command normalization & parsing skeleton
- [x] Help and version output

**Todo Features (Next Steps)**
- [ ] Design the core todo data structure
- [ ] `add`: Actually add a todo
- [ ] `list`: Implement an in-memory list
- [ ] `done`: Mark todos as completed
- [ ] `remove`: Delete a todo
- [ ] Implement local file storage
- [ ] Refactor into multiple source files as the codebase grows

## Usage

The parser currently recognizes the following commands. *(Note: `add`, `list`, `done`, and `remove` will trigger placeholder handlers for now).*

```bash
# Core commands
todo add "write README"
todo list
todo done 1
todo remove 1

# Help and Version
todo help      # or -h, --help
todo -v        # or --version
```
