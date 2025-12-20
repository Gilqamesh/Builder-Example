# Builder‑Example

A concise workspace demonstrating how to consume **Builder** as a module-based build orchestrator. For Builder internals and ABI details, see the [Builder](https://github.com/Gilqamesh/Builder) repository.

## Workspace layout
```
.
├─ modules/               # builder/ (submodule) + example modules
├─ artifacts/             # versioned build outputs
├─ run_latest_driver.cpp  # C++ helper to locate/run the latest builder_driver
├─ driver.sh              # build (if needed) + run a target module
├─ binary.sh              # run the latest-built binary for a module
├─ graph.svg              # graph of the modules/ folder
└─ LICENSE
```

## Usage

### Clone and init
```bash
git clone https://github.com/Gilqamesh/Builder-Example.git
cd Builder-Example
git submodule update --init --recursive
```

### driver.sh — build and run a target module
- Builds `builder_driver` if missing, then runs the requested module.
- `-g` runs under `gdb`, attached to the latest `builder_driver` invocation for the target.
```bash
./driver.sh <target_module>
./driver.sh <target_module> -g
```

### binary.sh — run the latest-built binary for a module
- Locates the newest artifact for `<target_module>` and executes `<binary_name>` from it.
```bash
./binary.sh <target_module> <binary_name>
```

### run_latest_driver.cpp — C++ helper
- Same purpose as `driver.sh`, implemented in C++.
- Builds (if needed) and runs the latest `builder_driver`, then invokes the target module.
```bash
clang++ -std=c++23 -o run_latest_driver run_latest_driver.cpp
./run_latest_driver <target_module>
```

## Graph (modules/)
![Module graph](graph.svg)

How to read it:
- Rounded boxes (SCCs) are strongly connected components of modules (those, whose runtime dependencies depend on each other).
- Boxes are modules.
- Solid arrows are **builder dependencies**.
- Dashed arrows are **module dependencies**.

## License
MIT. See `LICENSE`.