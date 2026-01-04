#include <format>
#include <iostream>
#include <string>
#include <filesystem>
#include <source_location>
#include <vector>

#include <unistd.h>
#include <cstring>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << std::format("usage: {} <module-name> [binary-relative-to-module + args...]", argv[0]) << std::endl;
        return 1;
    }

    try {
        const auto builder_dir = std::filesystem::path("builder");
        const auto modules_dir = std::filesystem::path("modules");
        const auto module_dir = std::filesystem::path(argv[1]);
        const auto artifacts_dir = std::filesystem::path("artifacts");

        const auto builder_cli_path = builder_dir / "cli";
        const auto builder_cli_src_path = builder_dir / "cli.cpp";

        const auto root_dir = builder_dir.parent_path().empty() ? "." : builder_dir.parent_path();

        {
            const auto cli = std::filesystem::canonical("/proc/self/exe");
            const auto cli_src = root_dir / std::filesystem::path(std::source_location::current().file_name());

            std::error_code ec;
            const auto cli_last_write_time = std::filesystem::last_write_time(cli, ec);
            if (ec) {
                throw std::runtime_error(std::format("failed to get last write time of cli '{}': {}", cli.string(), ec.message()));
            }

            const auto cli_src_last_write_time = std::filesystem::last_write_time(cli_src, ec);
            if (ec) {
                throw std::runtime_error(std::format("failed to get last write time of cli source '{}': {}", cli_src.string(), ec.message()));
            }

            if (cli_last_write_time < cli_src_last_write_time) {
                const auto command = std::format("clang++ -g -std=c++23 -o {} {}", cli.string(), cli_src.string());
                std::cout << command << std::endl;
                const int command_result = std::system(command.c_str());
                if (command_result != 0) {
                    throw std::runtime_error(std::format("failed to compile updated '{}', command exited with code {}", cli.string(), command_result));
                }

                if (!std::filesystem::exists(cli)) {
                    throw std::runtime_error(std::format("expected updated '{}' to exist but it does not", cli.string()));
                }

                std::string exec_command;
                std::vector<char*> exec_args;
                for (int i = 0; i < argc; ++i) {
                    exec_args.push_back(argv[i]);
                    if (!exec_command.empty()) {
                        exec_command += " ";
                    }
                    exec_command += argv[i];
                }
                exec_args.push_back(nullptr);

                std::cout << exec_command << std::endl;
                if (execv(cli.c_str(), exec_args.data()) == -1) {
                    throw std::runtime_error(std::format("failed to execv updated '{}': {}", cli.string(), std::strerror(errno)));
                }
            }
        }

        if (!std::filesystem::exists(builder_cli_path) || std::filesystem::last_write_time(builder_cli_path) < std::filesystem::last_write_time(builder_cli_src_path)) {
            const auto compile_cli_command = std::format("make -C \"{}\" cli", builder_dir.string());
            std::cout << compile_cli_command << std::endl;
            const int compile_cli_command_result = std::system(compile_cli_command.c_str());
            if (compile_cli_command_result) {
                throw std::runtime_error(std::format("failed to compile '{}', command exited with code '{}'", builder_cli_path.string(), compile_cli_command_result));
            }
        }

        if (!std::filesystem::exists(builder_cli_path)) {
            throw std::runtime_error(std::format("expected '{}' to exist but it does not", builder_cli_path.string()));
        }

        const auto run_builder_cli_command = std::format("./{} {} {} {} {}", builder_cli_path.string(), builder_dir.string(), modules_dir.string(), module_dir.string(), artifacts_dir.string());
        std::cout << run_builder_cli_command << std::endl;
        const int run_builder_cli_command_result = std::system(run_builder_cli_command.c_str());
        if (run_builder_cli_command_result) {
            throw std::runtime_error(std::format("failed to run '{}', command exited with code '{}'", builder_cli_path.string(), run_builder_cli_command_result));
        }

        if (3 <= argc) {
            const auto binary_relative_to_module = argv[2];
            const auto module_artifact_dir = artifacts_dir / module_dir;
            std::filesystem::path module_artifact_latest_versioned_dir;
            for (const auto& entry : std::filesystem::directory_iterator(module_artifact_dir)) {
                if (!entry.is_directory()) {
                    continue ;
                }
                const auto module_artifact_versioned_dir = entry.path();
                if (module_artifact_latest_versioned_dir < module_artifact_versioned_dir) {
                    module_artifact_latest_versioned_dir = module_artifact_versioned_dir;
                }
            }
            if (module_artifact_latest_versioned_dir.empty()) {
                throw std::runtime_error(std::format("expected at least one versioned artifact directory in '{}' but found none", module_artifact_dir.string()));
            }

            const auto module_binaries_path = module_artifact_latest_versioned_dir / "module";
            const auto binary_path = module_binaries_path / binary_relative_to_module;
            if (!std::filesystem::exists(binary_path)) {
                throw std::runtime_error(std::format("binary '{}' does not exist", binary_path.string()));
            }

            std::string binary_command = "./" + binary_path.string();
            for (int i = 3; i < argc; ++i) {
                binary_command += " " + std::string(argv[i]);
            }

            std::cout << binary_command << std::endl;
            std::system(binary_command.c_str());
        }
    } catch (std::exception& e) {
        std::cerr << std::format("{}: {}", argv[0], e.what()) << std::endl;
        return 1;
    }

    return 0;
}
