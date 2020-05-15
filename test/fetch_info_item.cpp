#include <napi.h>

#include "nhelper/fetch_info_item.h"
#include "nhelper/args_check.h"
#include "nhelper/type_converter.h"

Napi::Value ExportFetchInfoItem(const Napi::CallbackInfo& info) {
    Nhelper::CheckInfoLength(info, 2);
    Nhelper::CheckInfoType<int32_t>(info, 0);
    Nhelper::CheckInfoType<int32_t>(info, 1);

    using TypeList = std::tuple<int32_t, int32_t>;
    auto result = Nhelper::FetchInfoItem<1, TypeList>(info);
    return Nhelper::TypeConverter<int32_t>::ToJSValue(info.Env(), result);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("fetchInfoItem",
                Napi::Function::New(env, ExportFetchInfoItem));

    return exports;
}

NODE_API_MODULE(fetch_info_item, InitAll);
