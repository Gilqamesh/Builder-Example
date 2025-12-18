#include <modules/builder/builder_plugin.h>
#include <modules/builder/builder.h>

#include <string>

BUILDER_EXTERN void builder__build_self(builder_ctx_t* ctx, const builder_api_t* api) {
    builder_t::lib(ctx, api, { "F.cpp" }, {}, true);
    builder_t::lib(ctx, api, { "F.cpp" }, {}, false);
}

BUILDER_EXTERN void builder__build_module(builder_ctx_t* ctx, const builder_api_t* api, const char* static_libs) {
    builder_t::binary(ctx, api, { "main.cpp" }, { { "R_VALUE", std::to_string(5) } }, "f", { static_libs });
}
