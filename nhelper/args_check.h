#pragma once

#include <napi.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "type_converter.h"

namespace Nhelper {




inline void CheckInfoLength(const Napi::CallbackInfo& info, size_t expect_length) {
    if (info.Length() != expect_length) {
        std::stringstream ss;
        ss << "Wrong number of arguments! expect: " << expect_length
           << ", actual: " << info.Length();
        throw Napi::TypeError::New(info.Env(), ss.str());
    }
}

template <typename T>
inline void CheckInfoType(const Napi::CallbackInfo& info, size_t idx) {
    if (!TypeConverter<std::decay_t<T>>::IsConvertible(info[idx])) {
        std::stringstream ss;
        ss << "Type of arg " << idx << " is not matched! expect: "
           << TypeConverter<std::decay_t<T>>::TypeName()
           << ", actual: " << TypeName(info[idx]);
        throw Napi::TypeError::New(info.Env(), ss.str());
    }
}

inline void CheckInfoTypeIsFunction(const Napi::CallbackInfo& info, size_t idx) {
    if (!info[idx].IsFunction()) {
        std::stringstream ss;
        ss << "Type of arg " << idx << " is not matched! expect: Function"
           << ", actual: " << TypeName(info[idx]);
        throw Napi::TypeError::New(info.Env(), ss.str());
    }
}

namespace details {

template <typename... Args>
struct CheckInfoTypeImpl {
    static void Check(const Napi::CallbackInfo& info, size_t start_idx, size_t end_idx) {

    }
};


template <typename T, typename... Rest>
struct CheckInfoTypeImpl<T, Rest...> {
    static void Check(const Napi::CallbackInfo& info, size_t start_idx, size_t end_idx) {
        if (start_idx == end_idx) {
            return;
        }
        CheckInfoType<T>(info, start_idx);
    }
};


}


template <typename... Args>
inline avoid CheckInfoType(const Napi::CallbackInfo& info, size_t start_idx, size_t end_idx) {
    details::CheckInfoTypeImpl<Args...>::Check(info, start_idx, end_idx);
}


}  // namespace Nhelper
