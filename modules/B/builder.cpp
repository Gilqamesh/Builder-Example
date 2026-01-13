#include <builder/builder.h>
#include <builder/compiler/cpp_compiler.h>

BUILDER_EXTERN void builder__export_interface(const builder_t* builder, library_type_t library_type) {
    const auto interface_relative_path = relative_path_t("B.h");
    builder->install_interface(builder->source_dir() / interface_relative_path, interface_relative_path, library_type);
}

BUILDER_EXTERN void builder__export_libraries(const builder_t* builder, library_type_t library_type) {
    const auto lib_b_relative_path = relative_path_t("b");
    const auto lib_b = cpp_compiler_t::create_library(
        builder,
        filesystem_t::find(builder, filesystem_t::cpp_file, filesystem_t::descend_none),
        {},
        lib_b_relative_path,
        library_type
    );
    builder->install_library(lib_b, lib_b_relative_path, library_type);

}

BUILDER_EXTERN void builder__import_libraries(const builder_t* builder) {
}
