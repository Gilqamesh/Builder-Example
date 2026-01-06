#include <modules/builder/builder.h>
#include <modules/builder/compiler/cpp_compiler.h>
#include <modules/builder/find/find.h>

BUILDER_EXTERN void builder__export_libraries(const builder_t* builder, library_type_t library_type) {
    cpp_compiler_t::create_library(
        builder,
        find_t::find(builder, find_t::cpp_only && !find_t::filename("main.cpp"), false),
        {},
        "F",
        library_type
    );
}

BUILDER_EXTERN void builder__import_libraries(const builder_t* builder) {
    cpp_compiler_t::create_binary(
        builder,
        find_t::find(builder, find_t::filename("main.cpp"), false),
        { { "R_VALUE", std::to_string(5) } },
        LIBRARY_TYPE_STATIC,
        "f_static"
    );
    cpp_compiler_t::create_binary(
        builder,
        find_t::find(builder, find_t::filename("main.cpp"), false),
        { { "R_VALUE", std::to_string(5) } },
        LIBRARY_TYPE_SHARED,
        "f_shared"
    );
}
