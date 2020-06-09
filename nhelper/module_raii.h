#pragma once

#include <napi.h>

#include <functional>
#include <string>
#include <utility>
#include <iostream>
namespace Nhelper {

namespace {

class ModuleRAII : public Napi::ObjectWrap<ModuleRAII> {
public:
    using InitAction = std::function<void(void)>;
    using DeinitAction = std::function<void(void)>;

public:
    static Napi::Object NewInstance(Napi::Env env, Napi::Value init_action,
                                    Napi::Value deinit_action) {
        Napi::EscapableHandleScope scope(env);

        Napi::Function func = DefineClass(env, "ModuleRAII", {});

        constructor = Napi::Persistent(func);
        constructor.SuppressDestruct();

        Napi::Object object = constructor.New({init_action, deinit_action});
        return scope.Escape(napi_value(object)).ToObject();
    }

    explicit ModuleRAII(const Napi::CallbackInfo& info)
            : Napi::ObjectWrap<ModuleRAII>(info) {
        Napi::Function init_action_ = info[0].As<Napi::Function>();
        deinit_action_ = Napi::Persistent(info[1].As<Napi::Function>());

        init_action_.Call({});
    }

    ~ModuleRAII() {
        Napi::HandleScope scope(Env());
        deinit_action_.Call({});
    }

private:
    static Napi::FunctionReference constructor;
    Napi::FunctionReference deinit_action_;
};

Napi::FunctionReference ModuleRAII::constructor;

}  // namespace

inline void ModuleRAIIInit(Napi::Env env, Napi::Object exports,
                           const std::string& name,
                           ModuleRAII::InitAction init_action,
                           ModuleRAII::DeinitAction deinit_action) {
    exports.Set(name,
                ModuleRAII::NewInstance(
                        env,
                        Napi::Function::New(
                                env,
                                [init_action](const Napi::CallbackInfo& /* info */) {
                                    init_action();
                                }),
                        Napi::Function::New(
                                env, [deinit_action](
                                             const Napi::CallbackInfo& /* info */) {
                                    deinit_action();
                                })));
}

}  // namespace Nhelper
