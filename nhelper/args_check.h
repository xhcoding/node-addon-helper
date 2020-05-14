#pragma once

#include <napi.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "type_converter.h"

namespace Nhelper {

void CheckInfoLength(const Napi::CallbackInfo& info, size_t expect_length) {
    if (info.Length() != expect_length) {
        std::stringstream ss;
        ss << "Wrong number of arguments! expect: " << expect_length
           << ", actual: " << info.Length();
        throw Napi::TypeError::New(info.Env(), ss.str());
    }
}

template <typename T>
void CheckInfoType(const Napi::CallbackInfo& info, size_t idx) {
    if (!TypeConverter<std::decay_t<T>>::IsConvertible(info[idx])) {
        std::stringstream ss;
        ss << "Type of arg " << idx << " is not matched! expect: "
           << TypeConverter<std::decay_t<T>>::TypeName()
           << ", actual: " << TypeName(info[idx]);
        throw Napi::TypeError::New(info.Env(), ss.str());
    }
}

}  // namespace Nhelper
