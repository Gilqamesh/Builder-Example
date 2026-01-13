#include <builder/builder.h>
#include <builder/compiler/cpp_compiler.h>

BUILDER_EXTERN void builder__export_interface(const builder_t* builder, library_type_t library_type) {
    const auto interface_relative_path = relative_path_t("C.h");
    builder->install_interface(builder->source_dir() / interface_relative_path, interface_relative_path, library_type);
}

BUILDER_EXTERN void builder__export_libraries(const builder_t* builder, library_type_t library_type) {
    const auto lib_c_relative_path = relative_path_t("c");
    const auto lib_c = cpp_compiler_t::create_library(
        builder,
        filesystem_t::find(builder, filesystem_t::cpp_file, filesystem_t::descend_none),
        {},
        lib_c_relative_path,
        library_type
    );
    builder->install_library(lib_c, lib_c_relative_path, library_type);
}

BUILDER_EXTERN void builder__import_libraries(const builder_t* builder) {
}
