#include "nhelper/create_sync_method.h"

#include "nhelper/method_execute_exception.h"

int add(int a, int b) {
    return a + b;
}

void test(const std::string& /* message */, double /* b */) {}

std::string concat(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

int addThrow(int /* a */) {
    throw Nhelper::MethodExecuteException("add Throw");
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("add",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateSyncMethod(info, add);
                }));

    exports.Set("concat",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateSyncMethod(info, concat);
                }));

    exports.Set("returnVoid",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateSyncMethod(info, test);
                }));

    exports.Set("addThrow",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateSyncMethod(info, addThrow);
                }));

    return exports;
}

NODE_API_MODULE(create_async_worker, InitAll);
