# Builder‑Example

A collection of **small example modules** that demonstrate how to use the
[Builder](https://github.com/Gilqamesh/Builder) framework to build and compose
C++ modules. This repository does **not** implement Builder itself; instead,
it shows how to organize modules and invoke Builder to compile and link them.

## Goals

This repository is meant to be a learning resource for anyone who wants to:

- See concrete examples of how modules are laid out for Builder.
- Understand how dependencies between modules are declared and resolved.
- Learn how to build and run modules with the `builder` driver.

If you are looking for an application workspace that consumes modules as part
of a larger program, see the `Builder-Application-1` repository. If you need
Builder’s source code, refer to the `Builder` repository itself.

---

## Quick start (minimal setup)

The following commands show the smallest possible setup to get a working
Builder driver in this repository:

```bash
mkdir -p modules
git submodule add https://github.com/Gilqamesh/Builder.git modules/builder

clang++ -std=c++23 modules/builder/*.cpp -o driver
./driver <target_module>
```

Where:

- `<target_module>` is the name of a module directory under `modules/`
- Builder will discover dependencies, build itself if needed, and emit all
  artifacts under the `artifacts/` directory

This setup is intentionally explicit and avoids helper scripts so that the
build flow remains transparent.

---

## Repository layout

When populated with examples, the repository follows this structure:

```
.
├─ modules/            # Each sub-directory is a standalone module
│  ├─ builder/         # The Builder module itself (git submodule)
│  ├─ hello_world/     # Example executable module
│  ├─ math_utils/      # Example library module
│  └─ …
├─ artifacts/          # Builder writes all build outputs here (versioned)
└─ LICENSE             # MIT license
```

Notes:

- Each directory directly under `modules/` is treated as a module.
- Module names are derived from directory names.
- All outputs are written to `artifacts/<module>/<module>@<version>/`.

---

## Module anatomy

Each module must provide:

### 1. `deps.json`

Declares build-time and module-time dependencies.

```json
{
  "builder_deps": ["builder"],
  "module_deps": []
}
```

- `builder_deps`: required to *build* the module
- `module_deps`: required by produced artifacts

### 2. `builder_plugin.cpp`

Implements the build logic with C linkage:

```cpp
extern "C" void builder__build_self(builder_ctx_t*, const builder_api_t*);
extern "C" void builder__build_module(builder_ctx_t*, const builder_api_t*, const char*);
```

Inside these functions, call `builder_t::lib`, `builder_t::so`, or
`builder_t::binary` to emit artifacts.

---

## Building modules

Once modules exist under `modules/`, build a target module with:

```bash
./driver . modules <target_module> artifacts
```

Builder will:

- Validate dependency graphs
- Build modules in SCC/topological order
- Bundle static libraries per SCC
- Version and clean old artifacts automatically

---

## Running outputs

Artifacts are located under:

```
artifacts/<module>/<module>@<version>/
```

Executables can be run directly from that directory.
Libraries (`api.lib`, `api_pic.lib`, `api.so`) are consumed by dependent modules.

---

## License

MIT. See the `LICENSE` file for details.
