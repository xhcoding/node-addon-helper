#include "nhelper/args_check.h"

Napi::Value ExportCheckInfoLength(const Napi::CallbackInfo& info) {
    constexpr size_t length = 4;
    Nhelper::CheckInfoLength(info, length);
    return info.Env().Null();
}

template <typename T>
Napi::Value ExportCheckInfoType(const Napi::CallbackInfo& info) {
    Nhelper::CheckInfoType<T>(info, 0);
    return info.Env().Null();
}

Napi::Value ExportCheckInfoFunction(const Napi::CallbackInfo& info) {
    Nhelper::CheckInfoTypeIsFunction(info, 0);
    return info.Env().Null();
}


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("checkInfoLength",
                Napi::Function::New(env, ExportCheckInfoLength));
    exports.Set("checkInfoTypeBoolean",
                Napi::Function::New(env, ExportCheckInfoType<bool>));
    exports.Set("checkInfoTypeNumber",
                Napi::Function::New(env, ExportCheckInfoType<int32_t>));
    exports.Set("checkInfoTypeString",
                Napi::Function::New(env, ExportCheckInfoType<std::string>));
    exports.Set("checkInfoTypeVectorUint8_t",
                Napi::Function::New(env,
                                    ExportCheckInfoType<std::vector<uint8_t>>));
    exports.Set("checkInfoTypeVectorString",
                Napi::Function::New(
                        env, ExportCheckInfoType<std::vector<std::string>>));

    exports.Set("checkInfoTypeCharPointer",
                Napi::Function::New(env, ExportCheckInfoType<char*>));

    exports.Set("checkInfoTypeFunction",
                Napi::Function::New(env, ExportCheckInfoFunction));

    return exports;
}

NODE_API_MODULE(args_check, InitAll);
