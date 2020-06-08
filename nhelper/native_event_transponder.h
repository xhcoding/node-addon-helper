#pragma once

#include <napi.h>

#include "args_check.h"
#include "native_event_emitter.h"

namespace Nhelper {

namespace detail {

template <typename First, typename Second, typename... Args>
void ConstructNativeEventEmitter(Napi::ThreadSafeFunction* tsfn) {
    NativeEventEmitter<First>::Set(tsfn);
    ConstructNativeEventEmitter<Second, Args...>(tsfn);
}

template <typename Last>
void ConstructNativeEventEmitter(Napi::ThreadSafeFunction* tsfn) {
    NativeEventEmitter<Last>::Set(tsfn);
}

}  // namespace detail

template <typename... T>
class NativeEventTransponder
        : public Napi::ObjectWrap<NativeEventTransponder<T...>> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    explicit NativeEventTransponder(const Napi::CallbackInfo& info);

    ~NativeEventTransponder();

private:
    Napi::Value Release(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;

private:
    Napi::ThreadSafeFunction tsfn_;
};

template <typename... T>
Napi::FunctionReference NativeEventTransponder<T...>::constructor;

template <typename... T>
Napi::Object NativeEventTransponder<T...>::Init(Napi::Env env,
                                                Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func =
            DefineClass(env, "NativeEventTransponder",
                        {InstanceMethod("release", &NativeEventTransponder<T...>::Release)});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("NativeEventTransponder", func);
    return exports;
}

template <typename... T>
NativeEventTransponder<T...>::NativeEventTransponder(
        const Napi::CallbackInfo& info)
        : Napi::ObjectWrap<NativeEventTransponder>(info) {

    CheckInfoLength(info, 1);
    CheckInfoTypeIsFunction(info, 0);
    Napi::Function emit = info[0].As<Napi::Function>();
    tsfn_ = Napi::ThreadSafeFunction::New(info.Env(), emit,
                                          "NativeEventTransponder", 0, 1);
    detail::ConstructNativeEventEmitter<T...>(&tsfn_);
}

template <typename... T>
Napi::Value NativeEventTransponder<T...>::Release(const Napi::CallbackInfo& info) {
    tsfn_.Release();
    return Napi::Boolean::New(info.Env(), true);

}

template <typename... T>
NativeEventTransponder<T...>::~NativeEventTransponder() {
}

}  // namespace Nhelper
