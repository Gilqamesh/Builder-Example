# Builder‑Example

This repository provides a minimal workspace to demonstrate how to consume **Builder** as a module‑based build orchestrator. Its scope is deliberately narrow: learn how to add Builder as a dependency, define modules, declare dependencies and invoke the build. It is not a place to learn about Builder’s internal architecture; plugin authoring guidelines and ABI details live in the [Builder](./modules/builder) repository.

## Workspace layout

```
.
├─ modules/               # Contains one folder per module
│  ├─ builder/            # Builder module (git submodule)
│  ├─ <module>/           # Example modules
├─ artifacts/             # Versioned build outputs
├─ run_latest_driver.cpp  # Bootstrap driver
├─ *.sh                   # Optional wrapper scripts (run/debug)
└─ LICENSE
```

**Invariants**:

- Each directory under `modules/` is a module, and the module name equals its directory name.
- Modules declare dependencies in a `deps.json` file and implement build logic in a `builder_plugin.cpp` file.
- All build outputs go under the `artifacts/` directory in versioned subfolders.

## Bootstrapping the build

To set up a new workspace:

1. Create the `modules/` directory and initialize a git repository.
2. Add Builder as a submodule:

   ```bash
   git submodule add https://github.com/Gilqamesh/Builder.git modules/builder
   ```

3. Compile a one‑shot driver from Builder’s sources:

   ```bash
   clang++ -std=c++23 modules/builder/*.cpp -o builder_driver
   ```

   Then run the driver to build your target module:

   ```bash
   ./builder_driver <root_dir> <modules_dir> <module_name> <artifacts_dir>
   ```

   The driver locates modules, validates dependencies, builds Builder itself if necessary, and finally builds the requested module.

For convenience, the `run_latest_driver.cpp` in this repository locates the newest Builder artifact in `artifacts/builder/`. If no artifact exists, it compiles Builder from the submodule, runs it once to install itself into `artifacts/`, and removes the temporary binary before re‑running the installed Builder. Wrapper scripts like `run.sh` and `debug.sh` call the same logic but allow you to run or debug a module with minimal typing.

## Module anatomy

Each example module follows a simple contract:

- **`deps.json`** lists two arrays: `builder_deps` for modules needed to compile your plugin and `module_deps` for modules that your outputs depend on at link or runtime. Builder validates these graphs.
- **`builder_plugin.cpp`** defines two C‑linked functions—`builder__build_self` and `builder__build_module`—that build the module’s plugin and outputs, respectively. See the Builder README for authoring guidelines and the API definition.

Modules intended to be used as `builder_deps` must compile and export static libraries with position‑independent code (PIC) so that Builder can link them into plugins.

## Artifacts and versioning

Builder places build products in versioned directories under `artifacts/<module>/<module>@<version>/`. Versions are computed from the module’s source tree, its `deps.json`, and the versions of its builder dependencies. When you update a module or one of its dependencies, Builder computes a new version and writes fresh artifacts.

## License

This example uses the same MIT license as Builder. See `LICENSE`.
