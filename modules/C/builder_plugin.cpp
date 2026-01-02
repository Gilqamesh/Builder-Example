#include <builder/builder_plugin.h>
#include <builder/compiler.h>

BUILDER_EXTERN void builder__export_libraries(builder_ctx_t* ctx, const builder_api_t* api, bundle_type_t bundle_type) {
    compiler_t::create_library(
        ctx, api,
        { "C.cpp" },
        {},
        "c",
        bundle_type
    );
}

BUILDER_EXTERN void builder__build_module(builder_ctx_t* ctx, const builder_api_t* api) {
}
