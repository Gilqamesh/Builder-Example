# Builder‑Example

This repository is a minimal workspace demonstrating how to consume **Builder** as a module‑oriented build orchestrator. It shows how modules live in a workspace, how artifacts are versioned, and how to build and run modules using simple scripts. For more details on Builder’s internals and API, see the [Builder](https://github.com/Gilqamesh/Builder) repository.

## Contents

- [Quick start](#quick-start)
- [Module graph](#module-graph)
- [Requirements](#requirements)
- [License](#license)

## Quick start

1. **Clone and initialize submodules**

   ```bash
   git clone https://github.com/Gilqamesh/Builder-Example.git
   cd Builder-Example
   git submodule update --init --recursive
   ```

2. **Build a module** — compile a module and its dependencies, outputting to `artifacts/`:

   ```bash
   ./build.sh <module_name>
   ```

3. **Run a module’s binary** — run the most recent binary built for `<module_name>`, passing any extra arguments through:

   ```bash
   ./run.sh <module_name> <binary_name> [args...]
   ```

## Module graph

![Module graph](graph.svg)

The graph shows the dependency disposition between the modules:

- Rectangles represent individual modules.
- Solid arrows represent **builder plugin dependencies**.
- Dashed arrows represent **module dependencies**.
- Rounded rectangles represent strongly connected components that represents cyclic dependencies.

## Requirements

- Same as for the `Builder` module

## License

MIT. See `LICENSE`.
