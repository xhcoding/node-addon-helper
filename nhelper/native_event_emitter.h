#pragma once

#include <napi.h>

#include <functional>
#include <memory>
#include <string>

#include "type_converter.h"

namespace Nhelper {

template <typename T>
struct NativeEvent {
    std::string name;
    T data;
};

template <typename T>
class NativeEventEmitter {
public:
    static void Emit(const std::string& name, const T& data);

    static void Set(Napi::ThreadSafeFunction* tsfn);

    static void Unset();

private:
    explicit NativeEventEmitter();
    ~NativeEventEmitter() = default;

    static NativeEventEmitter& GetInstance();

    void InternalEmit(const std::string& name, const T& data) {
        auto callback = [](Napi::Env env, Napi::Function js_callback,
                           NativeEvent<T>* event) {
            js_callback.Call({Napi::String::New(env, event->name),
                              TypeConverter<T>::ToJSValue(env, event->data)});
            delete event;
        };

        if (!tsfn_) {
            return;
        }

        NativeEvent<T>* event = new NativeEvent<T>{name, data};

        napi_status status = tsfn_->BlockingCall(event, callback);
        if (status != napi_ok) {
            delete event;
        }
    }

private:
    Napi::ThreadSafeFunction* tsfn_;
};

template <typename T>
NativeEventEmitter<T>::NativeEventEmitter() {}

template <typename T>
NativeEventEmitter<T>& NativeEventEmitter<T>::GetInstance() {
    static NativeEventEmitter emitter;
    return emitter;
}

template <typename T>
void NativeEventEmitter<T>::Set(Napi::ThreadSafeFunction* tsfn) {
    GetInstance().tsfn_ = tsfn;
}

template <typename T>
void NativeEventEmitter<T>::Unset() {
    GetInstance().tsfn = nullptr;
}

template <typename T>
void NativeEventEmitter<T>::Emit(const std::string& name, const T& data) {
    GetInstance().InternalEmit(name, data);
}

}  // namespace Nhelper
