#pragma once

#include <napi.h>

#include <string>
#include <type_traits>
#include <utility>

// for debug
#include <iostream>

namespace Nhelper {

template <typename T, typename SFINAE = void>
class TypeConverter;

// bool

template <>
class TypeConverter<bool> {
public:
    static std::string TypeName() {
        return "Boolean";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsBoolean();
    }

    static bool ToNativeValue(const Napi::Value& value) {
        return value.As<Napi::Boolean>().Value();
    }

    static Napi::Value ToJSValue(const Napi::Env env, bool value) {
        return Napi::Boolean::New(env, value);
    }
};

template <typename T>
class TypeConverter<T, std::enable_if_t<std::is_integral<T>::value &&
                                        std::is_signed<T>::value>> {
public:
    static std::string TypeName() {
        return "Number";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsNumber();
    }

    static T ToNativeValue(const Napi::Value& value) {
        return static_cast<T>(value.As<Napi::Number>().Int64Value());
    }

    static Napi::Value ToJSValue(const Napi::Env env, T value) {
        return Napi::Number::New(env, static_cast<double>(value));
    }
};

template <typename T>
class TypeConverter<T, std::enable_if_t<std::is_integral<T>::value &&
                                        !std::is_signed<T>::value &&
                                        !std::is_same<bool, T>::value>> {
public:
    static std::string TypeName() {
        return "Number";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsNumber();
    }

    static T ToNativeValue(const Napi::Value& value) {
        return static_cast<T>(value.As<Napi::Number>().Uint32Value());
    }

    static Napi::Value ToJSValue(const Napi::Env env, T value) {
        return Napi::Number::New(env, static_cast<double>(value));
    }
};

template <>
class TypeConverter<float> {
public:
    static std::string TypeName() {
        return "Number";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsNumber();
    }

    static float ToNativeValue(const Napi::Value& value) {
        return value.As<Napi::Number>().FloatValue();
    }

    static Napi::Value ToJSValue(const Napi::Env env, float value) {
        return Napi::Number::New(env, static_cast<double>(value));
    }
};

template <>
class TypeConverter<double> {
public:
    static std::string TypeName() {
        return "Number";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsNumber();
    }

    static double ToNativeValue(const Napi::Value& value) {
        return value.As<Napi::Number>().FloatValue();
    }

    static Napi::Value ToJSValue(const Napi::Env env, double value) {
        return Napi::Number::New(env, value);
    }
};

template <>
class TypeConverter<std::string> {
public:
    static std::string TypeName() {
        return "String";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsString();
    }

    static std::string ToNativeValue(const Napi::Value& value) {
        return value.As<Napi::String>().Utf8Value();
    }

    static Napi::Value ToJSValue(const Napi::Env env,
                                 const std::string& value) {
        return Napi::String::New(env, value);
    }

    static Napi::Value ToJSValue(const Napi::Env env, const char* value) {
        return Napi::String::New(env, value);
    }

    static Napi::Value ToJSValue(const Napi::Env env, const char* value,
                                 size_t length) {
        return Napi::String::New(env, value, length);
    }
};

namespace details {

// TODO: refactor
template <typename T>
class TypeConverterVectorIntegralImpl;

template <typename T>
class TypeConverterVectorIntegralImpl<std::vector<T>> {
public:
    static std::string TypeName() {
        return "Array|ArrayBuffer|Buffer|TypedArray";
    }

    static bool IsConvertible(const Napi::Value& value) {
        if (value.IsArray()) {
            Napi::Array arr = value.As<Napi::Array>();
            for (uint32_t i = 0; i < arr.Length(); ++i) {
                if (!TypeConverter<T>::IsConvertible(arr[i])) {
                    return false;
                }
            }
            return true;
        } else if (value.IsArrayBuffer()) {
            Napi::ArrayBuffer arr = value.As<Napi::ArrayBuffer>();
            if (arr.ByteLength() % sizeof(T) == 0) {
                return true;
            }
            return false;
        } else if (value.IsBuffer()) {
            return true;
        }
        return false;
    }

    static std::vector<T> ToNativeValue(const Napi::Value& value) {
        std::vector<T> result;
        if (value.IsArray()) {
            Napi::Array arr = value.As<Napi::Array>();
            result.reserve(arr.Length());
            for (uint32_t i = 0; i < arr.Length(); ++i) {
                result.push_back(TypeConverter<T>::ToNativeValue(arr[i]));
            }
            return result;
        } else if (value.IsArrayBuffer()) {
            Napi::ArrayBuffer arr = value.As<Napi::ArrayBuffer>();
            size_t length = arr.ByteLength() / sizeof(T);
            result.reserve(length);
            void* data = arr.Data();
            for (uint32_t i = 0; i < length; i++) {
                result.push_back(*(reinterpret_cast<T*>(data) + i));
            }
        } else if (value.IsBuffer()) {
            Napi::Buffer<T> buffer = value.As<Napi::Buffer<T>>();
            size_t length = buffer.Length();
            T* data = buffer.Data();
            result.reserve(length);
            for (uint32_t i = 0; i < length; i++) {
                result.push_back(data[i]);
            }
        }
        return result;
    }

    static Napi::Value ToJSValue(const Napi::Env env,
                                 const std::vector<T>& value) {
        Napi::Array ret = Napi::Array::New(env, value.size());
        for (uint32_t i = 0; i < value.size(); ++i) {
            ret[i] = TypeConverter<T>::ToJSValue(env, value[i]);
        }
        return ret;
    }
};

template <typename T>
class TypeConverterVectorCommonImpl;

template <typename T>
class TypeConverterVectorCommonImpl<std::vector<T>> {
public:
    static std::string TypeName() {
        return "Array";
    }

    static bool IsConvertible(const Napi::Value& value) {
        if (!value.IsArray()) {
            return false;
        }
        Napi::Array arr = value.As<Napi::Array>();
        for (uint32_t i = 0; i < arr.Length(); ++i) {
            if (!TypeConverter<T>::IsConvertible(arr[i])) {
                return false;
            }
        }

        return false;
    }

    static std::vector<T> ToNativeValue(const Napi::Value& value) {
        std::vector<T> result;

        Napi::Array arr = value.As<Napi::Array>();
        result.reserve(arr.Length());
        for (uint32_t i = 0; i < arr.Length(); ++i) {
            result.push_back(TypeConverter<T>::ToNativeValue(arr[i]));
        }

        return result;
    }

    static Napi::Value ToJSValue(const Napi::Env env,
                                 const std::vector<T>& value) {
        Napi::Array ret = Napi::Array::New(env, value.size());
        for (uint32_t i = 0; i < value.size(); ++i) {
            ret[i] = TypeConverter<T>::ToJSValue(env, value[i]);
        }
        return ret;
    }
};

}  // namespace details

template <typename T>
class TypeConverter<std::vector<T>> {
public:
    using TypeConverterImpl = typename std::conditional<
            std::is_integral<T>::value || std::is_floating_point<T>::value,
            details::TypeConverterVectorIntegralImpl<std::vector<T>>,
            details::TypeConverterVectorCommonImpl<std::vector<T>>>::type;

    static std::string TypeName() {
        return TypeConverterImpl::TypeName();
    }

    static bool IsConvertible(const Napi::Value& value) {
        return TypeConverterImpl::IsConvertible(value);
    }

    static std::vector<T> ToNativeValue(const Napi::Value& value) {
        return TypeConverterImpl::ToNativeValue(value);
    }

    static Napi::Value ToJSValue(const Napi::Env env,
                                 const std::vector<T>& value) {
        return TypeConverterImpl::ToJSValue(env, value);
    }
};

template <>
class TypeConverter<char*> {
public:
    static std::string TypeName() {
        return "ArrayBuffer|Buffer|TypedArray";
    }

    static bool IsConvertible(const Napi::Value& value) {
        return value.IsArrayBuffer() || value.IsTypedArray() ||
               value.IsBuffer();
    }

    static std::pair<const char*, size_t> ToNativeValue(
            const Napi::Value& value) {
        if (value.IsArrayBuffer()) {
            Napi::ArrayBuffer arr = value.As<Napi::ArrayBuffer>();
            return std::make_pair(reinterpret_cast<char*>(arr.Data()),
                                  arr.ByteLength());
        } else if (value.IsBuffer()) {
            Napi::Buffer<char> buffer = value.As<Napi::Buffer<char>>();
            return std::make_pair(buffer.Data(), buffer.Length());
        }
        return std::make_pair(nullptr, 0);
    }

    static Napi::Value ToJSValue(const Napi::Env env,
                                 const std::pair<const char*, size_t>& value) {
        return Napi::Buffer<char>::Copy(env, value.first, value.second);
    }
};


inline std::string TypeName(const Napi::Value& value) {
    if (value.IsUndefined()) {
        return "Undefined";
    } else if (value.IsNull()) {
        return "Null";
    } else if (value.IsBoolean()) {
        return "Boolean";
    } else if (value.IsString()) {
        return "String";
    } else if (value.IsNumber()) {
        return "Number";
    } else if (value.IsArray()) {
        return "Array";
    } else if (value.IsArrayBuffer()) {
        return "ArrayBuffer";
    } else if (value.IsTypedArray()) {
        return "TypedArray";
    } else if (value.IsFunction()) {
        return "Function";
    } else if (value.IsObject()) {
        return "Object";
    }
    return "Unknow";
}


template <typename T>
inline auto ToNativeValue(const Napi::Value& value) {
    return TypeConverter<T>::ToNativeValue(value);
}

template <typename T>
inline auto ToJSValue(Napi::Env env, const T& t) {
    return TypeConverter<T>::ToJSValue(env, t);
}


}  // namespace Nhelper
