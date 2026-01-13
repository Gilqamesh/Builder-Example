#include <builder/builder.h>
#include <builder/compiler/cpp_compiler.h>

BUILDER_EXTERN void builder__export_interface(const builder_t* builder, library_type_t library_type) {
    const auto interface_relative_path = relative_path_t("F.h");
    builder->install_interface(builder->source_dir() / interface_relative_path, interface_relative_path, library_type);
}

BUILDER_EXTERN void builder__export_libraries(const builder_t* builder, library_type_t library_type) {
    const auto lib_f_relative_path = relative_path_t("f");
    const auto lib_f = cpp_compiler_t::create_library(
        builder,
        filesystem_t::find(builder, filesystem_t::cpp_file && !filesystem_t::filename("main.cpp"), filesystem_t::descend_none),
        {},
        lib_f_relative_path,
        library_type
    );
    builder->install_library(lib_f, lib_f_relative_path, library_type);
}

BUILDER_EXTERN void builder__import_libraries(const builder_t* builder) {
    const auto static_binary_relative_path = relative_path_t("f_static");
    const auto static_binary_f = cpp_compiler_t::create_binary(
        builder,
        filesystem_t::find(builder, filesystem_t::filename("main.cpp"), filesystem_t::descend_none),
        { { "R_VALUE", std::to_string(5) } },
        library_type_t::STATIC,
        static_binary_relative_path
    );
    builder->install_import(static_binary_f, static_binary_relative_path);

    const auto shared_binary_relative_path = relative_path_t("f_shared");
    const auto shared_binary_f = cpp_compiler_t::create_binary(
        builder,
        filesystem_t::find(builder, filesystem_t::filename("main.cpp"), filesystem_t::descend_none),
        { { "R_VALUE", std::to_string(5) } },
        library_type_t::SHARED,
        shared_binary_relative_path
    );
    builder->install_import(shared_binary_f, shared_binary_relative_path);
}
