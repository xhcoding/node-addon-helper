#include <napi.h>
#include "nhelper/apply.h"
#include "nhelper/args_check.h"
#include "nhelper/type_converter.h"

int Add(int a, int b) {
    return a + b;
}

Napi::Value ExportApply(const Napi::CallbackInfo& info) {
    Nhelper::CheckInfoLength(info, 2);
    Nhelper::CheckInfoType<int32_t>(info, 0);
    Nhelper::CheckInfoType<int32_t>(info, 1);
    int a = Nhelper::TypeConverter<int32_t>::ToNativeValue(info[0]);
    int b = Nhelper::TypeConverter<int32_t>::ToNativeValue(info[1]);
    auto t = std::make_tuple(a, b);
    auto result = Nhelper::Apply(Add, t);
    return Nhelper::TypeConverter<int32_t>::ToJSValue(info.Env(), result);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("apply",
                Napi::Function::New(env, ExportApply));

    return exports;
}

NODE_API_MODULE(apply, InitAll);
