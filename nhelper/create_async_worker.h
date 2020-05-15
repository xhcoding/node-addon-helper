#pragma once

#include <napi.h>

#include "args_check.h"
#include "fetch_info_item.h"
#include "type_converter.h"
#include "apply.h"
#include "worker_execute_exception.h"

namespace Nhelper {

namespace details {

template <typename Result, typename Api, typename... Args>
class ApiAsyncWorker : public Napi::AsyncWorker {
public:
    using OKHandler = void (*)(Napi::Env& env,
                               Napi::FunctionReference& callback, const Result& r);
    using ErrorHandler = void (*)(Napi::Env& env,
                                  Napi::FunctionReference& callback,
                                  std::string error);

public:
    ApiAsyncWorker(Napi::Function& callback, const Api& api, Args&&... args)
            : Napi::AsyncWorker(callback),
              api_(api),
              args_(args...),
              ok_handler_(nullptr),
              error_handler_(nullptr) {}

public:
    template <typename F>
    ApiAsyncWorker& SetOKHandler(F ok_handler) {
        ok_handler_ = ok_handler;
        return *this;
    }

    ApiAsyncWorker& SetOKHandler(OKHandler ok_handler) {
        ok_handler_ = ok_handler;
        return *this;
    }

    ApiAsyncWorker& SetErrorHandler(ErrorHandler& error_handler) {
        error_handler_ = error_handler;
        return *this;
    }

protected:
    void Execute() override {
        try {
            result_ = Apply(api_, args_);
        } catch (const WorkerExecuteException& e) {
            SetError(e.what());
        } catch (...) {
            SetError("uncatched exception.");
        }
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        if (ok_handler_) {
            ok_handler_(Env(), Callback(), result_);
        } else {
            Callback().Call(
                    {Env().Undefined(),
                     TypeConverter<Result>::ToJSValue(Env(), result_)});
        }
    }

    void OnError(const Napi::Error& error) override {
        Napi::HandleScope scope(Env());
        if (error_handler_) {
            error_handler_(Env(), Callback(), error.what());
        } else {
            Callback().Call({Napi::String::New(Env(), error.what()),
                             Env().Undefined()});
        }
    }

private:
    Api api_;
    std::tuple<Args...> args_;
    Result result_;

    OKHandler ok_handler_;
    ErrorHandler error_handler_;
};

template <typename Api, typename... Args>
class ApiAsyncWorker<void, Api, Args...> : public Napi::AsyncWorker {
public:
    using OKHandler = void (*)(Napi::Env& env,
                               Napi::FunctionReference& callback);
    using ErrorHandler = void (*)(Napi::Env& env,
                                  Napi::FunctionReference& callback,
                                  std::string error);

public:
    ApiAsyncWorker(Napi::Function& callback, const Api& api, Args&&... args)
            : Napi::AsyncWorker(callback),
              api_(api),
              args_(args...),
              ok_handler_(nullptr),
              error_handler_(nullptr) {}

public:
    template <typename F>
    ApiAsyncWorker& SetOKHandler(F ok_handler) {
        ok_handler_ = ok_handler;
        return *this;
    }

    ApiAsyncWorker& SetOKHandler(OKHandler& ok_handler) {
        ok_handler_ = ok_handler;
        return *this
    }

    ApiAsyncWorker& SetErrorHandler(ErrorHandler& error_handler) {
        error_handler_ = error_handler;
        return *this
    }

protected:
    void Execute() override {
        try {
            Apply(api_, args_);
        } catch (const WorkerExecuteException& e) {
            SetError(e.what());
        } catch (...) {
            SetError("uncatched exception.");
        }
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        if (ok_handler_) {
            ok_handler_(Env(), Callback());
        } else {
            Callback().Call({Env().Undefined()});
        }
    }

    void OnError(const Napi::Error& error) override {
        Napi::HandleScope scope(Env());
        if (error_handler_) {
            error_handler_(Env(), Callback(), error.what());
        } else {
            Callback().Call({Napi::String::New(Env(), error.what()),
                             Env().Undefined()});
        }
    }

private:
    Api api_;
    std::tuple<Args...> args_;

    OKHandler ok_handler_;
    ErrorHandler error_handler_;
};

template <typename R, typename... Args, size_t... Indices>
auto& MakeWorker(const Napi::CallbackInfo& info, R (*f)(Args...),
                 std::index_sequence<Indices...>) {
    using TypeList = std::tuple<std::decay_t<Args>...>;

    ApiAsyncWorker<R, decltype(f), std::decay_t<Args>...>* worker =
            new ApiAsyncWorker<R, decltype(f), std::decay_t<Args>...>(
                    info[sizeof...(Args)].As<Napi::Function>(), f,
                    FetchInfoItem<Indices, TypeList>(info)...);
    return *worker;
}

template <typename... Args, size_t... Indices>
auto& MakeWorker(const Napi::CallbackInfo& info, void (*f)(Args...),
                 std::index_sequence<Indices...>) {
    using TypeList = std::tuple<std::decay_t<Args>...>;

    ApiAsyncWorker<void, decltype(f), std::decay_t<Args>...>* worker =
            new ApiAsyncWorker<void, decltype(f), std::decay_t<Args>...>(
                    info[sizeof...(Args)].As<Napi::Function>(), f,
                    FetchInfoItem<Indices, TypeList>(info)...);
    return *worker;
}

}  // namespace details

template <typename R, typename... Args>
auto& CreateAsyncWorker(const Napi::CallbackInfo& info, R (*f)(Args...)) {
    constexpr size_t num_args = sizeof...(Args);
    CheckInfoLength(info, num_args + 1);
    CheckInfoType<std::decay_t<Args>...>(info, 0, num_args);
    CheckInfoTypeIsFunction(info, num_args);
    return details::MakeWorker(info, f, std::make_index_sequence<num_args>());
}

template <typename... Args>
auto& CreateAsyncWorker(const Napi::CallbackInfo& info, void (*f)(Args...)) {
    constexpr size_t num_args = sizeof...(Args);
    CheckInfoLength(info, num_args + 1);
    CheckInfoType<std::decay_t<Args>...>(info, 0, num_args);
    CheckInfoTypeIsFunction(info, num_args);
    return details::MakeWorker(info, f, std::make_index_sequence<num_args>());
}

}  // namespace Nhelper
