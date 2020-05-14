#include "nhelper/type_converter.h"

template <typename T>
Napi::Value ExportConvertToT(const Napi::CallbackInfo& info) {
    return Nhelper::TypeConverter<T>::ToJSValue(
            info.Env(), Nhelper::TypeConverter<T>::ToNativeValue(info[0]));
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("convertBool",
                Napi::Function::New(env, ExportConvertToT<bool>));
    exports.Set("convertInt8_t",
                Napi::Function::New(env, ExportConvertToT<int8_t>));
    exports.Set("convertUint8_t",
                Napi::Function::New(env, ExportConvertToT<uint8_t>));
    exports.Set("convertInt16_t",
                Napi::Function::New(env, ExportConvertToT<int16_t>));
    exports.Set("convertUint16_t",
                Napi::Function::New(env, ExportConvertToT<uint16_t>));
    exports.Set("convertInt32_t",
                Napi::Function::New(env, ExportConvertToT<int32_t>));
    exports.Set("convertUint32_t",
                Napi::Function::New(env, ExportConvertToT<uint32_t>));
    exports.Set("convertInt64_t",
                Napi::Function::New(env, ExportConvertToT<int64_t>));
    exports.Set("convertFloat",
                Napi::Function::New(env, ExportConvertToT<float>));
    exports.Set("convertDouble",
                Napi::Function::New(env, ExportConvertToT<double>));
    exports.Set("convertString",
                Napi::Function::New(env, ExportConvertToT<std::string>));
    exports.Set(
            "convertVectorInt8_t",
            Napi::Function::New(env, ExportConvertToT<std::vector<int8_t>>));
    exports.Set(
            "convertVectorUint8_t",
            Napi::Function::New(env, ExportConvertToT<std::vector<uint8_t>>));
    exports.Set(
            "convertVectorInt16_t",
            Napi::Function::New(env, ExportConvertToT<std::vector<int16_t>>));
    exports.Set(
            "convertVectorUint16_t",
            Napi::Function::New(env, ExportConvertToT<std::vector<uint16_t>>));
    exports.Set(
            "convertVectorInt32_t",
            Napi::Function::New(env, ExportConvertToT<std::vector<int32_t>>));

    exports.Set(
            "convertVectorUint32_t",
            Napi::Function::New(env, ExportConvertToT<std::vector<uint32_t>>));
    exports.Set("convertVectorFloat",
                Napi::Function::New(env, ExportConvertToT<std::vector<float>>));
    exports.Set(
            "convertVectorDouble",
            Napi::Function::New(env, ExportConvertToT<std::vector<double>>));
    exports.Set("convertVectorString",
                Napi::Function::New(
                        env, ExportConvertToT<std::vector<std::string>>));
    exports.Set("convertCharPointer",
                Napi::Function::New(env, ExportConvertToT<char*>));

    return exports;
}

NODE_API_MODULE(type_converter, InitAll);
