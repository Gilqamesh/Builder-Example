#include <builder/builder_plugin.h>
#include <builder/compiler/cpp_compiler.h>
#include <builder/find/find.h>

BUILDER_EXTERN void builder__export_libraries(builder_ctx_t* ctx, const builder_api_t* api, bundle_type_t bundle_type) {
    cpp_compiler_t::create_library(
        ctx, api,
        find_t::find(ctx, api, find_t::cpp_only && !find_t::filename("main.cpp"), false),
        {},
        "E",
        bundle_type
    );
}

BUILDER_EXTERN void builder__build_module(builder_ctx_t* ctx, const builder_api_t* api) {
    cpp_compiler_t::create_binary(
        ctx, api,
        find_t::find(ctx, api, find_t::filename("main.cpp"), false),
        {},
        BUNDLE_TYPE_STATIC,
        "e"
    );
}
