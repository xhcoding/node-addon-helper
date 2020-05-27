#pragma once

#include <napi.h>

#include "apply.h"
#include "args_check.h"
#include "fetch_info_item.h"
#include "type_converter.h"
#include "method_execute_exception.h"

namespace Nhelper {

namespace details {

template <typename Result, typename Api, typename... Args>
class ApiAsyncWorker : public Napi::AsyncWorker {
public:
    ApiAsyncWorker(Napi::Env env, const Api& api, Args&&... args)
            : Napi::AsyncWorker(env),
              deferred_(Napi::Promise::Deferred::New(env)),
              api_(api),
              args_(args...) {}

public:
    Napi::Value Queue() {
        Napi::AsyncWorker::Queue();
        return deferred_.Promise();
    }

protected:
    void Execute() override {
        try {
            result_ = Apply(api_, args_);
        } catch (const MethodExecuteException& e) {
            SetError(e.what());
        } catch (...) {
            SetError("uncatched exception.");
        }
    }

    void OnOK() override {
        deferred_.Resolve(TypeConverter<Result>::ToJSValue(Env(), result_));
    }

    void OnError(const Napi::Error& error) override {
        deferred_.Reject(error.Value());
    }

private:
    Api api_;
    std::tuple<Args...> args_;
    Result result_;

    Napi::Promise::Deferred deferred_;
};

template <typename Api, typename... Args>
class ApiAsyncWorker<void, Api, Args...> : public Napi::AsyncWorker {
public:
    ApiAsyncWorker(Napi::Env env, const Api& api, Args&&... args)
            : Napi::AsyncWorker(env),
              deferred_(Napi::Promise::Deferred::New(env)),
              api_(api),
              args_(args...) {}

public:
    Napi::Value Queue() {
        Napi::AsyncWorker::Queue();
        return deferred_.Promise();
    }

protected:
    void Execute() override {
        try {
            Apply(api_, args_);
        } catch (const MethodExecuteException& e) {
            SetError(e.what());
        } catch (...) {
            SetError("uncatched exception.");
        }
    }

    void OnOK() override {
        deferred_.Resolve(Env().Null());
    }

    void OnError(const Napi::Error& error) override {
        deferred_.Reject(error.Value());
    }

private:
    Api api_;
    std::tuple<Args...> args_;

    Napi::Promise::Deferred deferred_;
};

template <typename R, typename... Args, size_t... Indices>
auto& MakeWorker(const Napi::CallbackInfo& info, R (*f)(Args...),
                 std::index_sequence<Indices...>) {
    using TypeList = std::tuple<std::decay_t<Args>...>;

    ApiAsyncWorker<R, decltype(f), std::decay_t<Args>...>* worker =
            new ApiAsyncWorker<R, decltype(f), std::decay_t<Args>...>(
                    info.Env(), f, FetchInfoItem<Indices, TypeList>(info)...);
    return *worker;
}

template <typename... Args, size_t... Indices>
auto& MakeWorker(const Napi::CallbackInfo& info, void (*f)(Args...),
                 std::index_sequence<Indices...>) {
    using TypeList = std::tuple<std::decay_t<Args>...>;

    ApiAsyncWorker<void, decltype(f), std::decay_t<Args>...>* worker =
            new ApiAsyncWorker<void, decltype(f), std::decay_t<Args>...>(
                    info.Env(), f, FetchInfoItem<Indices, TypeList>(info)...);
    return *worker;
}

}  // namespace details

template <typename R, typename... Args>
inline Napi::Value CreateAsyncWorker(const Napi::CallbackInfo& info,
                               R (*f)(Args...)) {
    constexpr size_t num_args = sizeof...(Args);
    CheckInfoLength(info, num_args);
    CheckInfoType<std::decay_t<Args>...>(info, 0, num_args);
    return details::MakeWorker(info, f, std::make_index_sequence<num_args>()).Queue();
}

template <typename... Args>
inline Napi::Value CreateAsyncWorker(const Napi::CallbackInfo& info,
                               void (*f)(Args...)) {
    constexpr size_t num_args = sizeof...(Args);
    CheckInfoLength(info, num_args);
    CheckInfoType<std::decay_t<Args>...>(info, 0, num_args);
    return details::MakeWorker(info, f, std::make_index_sequence<num_args>()).Queue();
}

}  // namespace Nhelper
