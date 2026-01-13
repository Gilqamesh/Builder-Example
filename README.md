# Builder‑Example

This repository is a minimal workspace demonstrating how to use `Builder`. For more details on Builder’s internals and API, see the [Builder](https://github.com/Gilqamesh/Builder) repository.

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

2. **Bootstrap Builder**

   This builds the Builder CLI from the `builder` module and installs it into the artifacts directory.

   ```bash
   make -f modules/builder/bootstrap.mk bootstrap MODULES_DIR=modules ARTIFACTS_DIR=artifacts
   ```

3. **Build a target module**

   This command builds the target module `F`.

   ```bash
   ./artifacts/builder/alias/import/install/cli modules F artifacts
   ```

   If a binary name is provided, the CLI executes that binary and forwards all remaining arguments to it.

   ```bash
   ./artifacts/builder/alias/import/install/cli modules F artifacts f_shared
   ```

## Module graph

The graph shows the dependency structure between the modules.
- Rectangles represent individual modules.
- Arrows represent dependency relations.
- Rounded rectangles represent strongly connected components, where each module is cyclically dependent on all the others.

![Module graph](graph.svg)

## Requirements

- Requirements of [Builder](https://github.com/Gilqamesh/Builder)

## License

See [LICENSE](LICENSE).
