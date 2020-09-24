#pragma once

#include <napi.h>

#include <exception>

#include "args_check.h"
#include "fetch_info_item.h"
#include "method_execute_exception.h"

namespace Nhelper {

namespace details {

template <typename R, typename... Args, size_t... Indices>
R Call(const Napi::CallbackInfo& info, R (*f)(Args...),
       std::index_sequence<Indices...>) {
    using TypeList = std::tuple<std::decay_t<Args>...>;
    try {
        return f(FetchInfoItem<Indices, TypeList>(info)...);
    } catch (const std::exception& exc) {
        throw Napi::Error::New(info.Env(), exc.what());
    } catch (...) {
        throw Napi::Error::New(info.Env(), "Unknow exception");
    }
}

template <typename... Args, size_t... Indices>
void Call(const Napi::CallbackInfo& info, void (*f)(Args...),
          std::index_sequence<Indices...>) {
    using TypeList = std::tuple<std::decay_t<Args>...>;
    try {
        f(FetchInfoItem<Indices, TypeList>(info)...);
    } catch (const std::exception& exc) {
        throw Napi::Error::New(info.Env(), exc.what());
    } catch (...) {
        throw Napi::Error::New(info.Env(), "Unknow exception");
    }
}

}  // namespace details

template <typename R, typename... Args>
inline Napi::Value CreateSyncMethod(const Napi::CallbackInfo& info,
                                    R (*f)(Args...)) {
    constexpr size_t num_args = sizeof...(Args);
    CheckInfoLength(info, num_args);
    CheckInfoType<std::decay_t<Args>...>(info, 0, num_args);
    return TypeConverter<R>::ToJSValue(
            info.Env(),
            details::Call(info, f, std::make_index_sequence<num_args>()));
}

template <typename... Args>
inline Napi::Value CreateSyncMethod(const Napi::CallbackInfo& info,
                                    void (*f)(Args...)) {
    constexpr size_t num_args = sizeof...(Args);
    CheckInfoLength(info, num_args);
    CheckInfoType<std::decay_t<Args>...>(info, 0, num_args - 1);
    details::Call(info, f, std::make_index_sequence<num_args>());
    return info.Env().Null();
}

}  // namespace Nhelper
