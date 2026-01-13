#include <builder/builder.h>
#include <builder/compiler/cpp_compiler.h>

BUILDER_EXTERN void builder__export_interface(const builder_t* builder, library_type_t library_type) {
    const auto interface_relative_path = relative_path_t("E.h");
    builder->install_interface(builder->source_dir() / interface_relative_path, interface_relative_path, library_type);
}

BUILDER_EXTERN void builder__export_libraries(const builder_t* builder, library_type_t library_type) {
    const auto lib_e_relative_path = relative_path_t("e");
    const auto lib_e = cpp_compiler_t::create_library(
        builder,
        filesystem_t::find(builder, filesystem_t::cpp_file && !filesystem_t::filename("main.cpp"), filesystem_t::descend_none),
        {},
        lib_e_relative_path,
        library_type
    );
    builder->install_library(lib_e, lib_e_relative_path, library_type);
}

BUILDER_EXTERN void builder__import_libraries(const builder_t* builder) {
    const auto binary_relative_path = relative_path_t("e");
    const auto binary_e = cpp_compiler_t::create_binary(
        builder,
        filesystem_t::find(builder, filesystem_t::filename("main.cpp"), filesystem_t::descend_none),
        {},
        library_type_t::STATIC,
        binary_relative_path
    );
    builder->install_import(binary_e, binary_relative_path);
}
