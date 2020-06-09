#include "nhelper/create_async_worker.h"

int add(int a, int b) {
    return a + b;
}

void test(const std::string& /* message */, double /* b */) {}

std::string concat(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

int addThrow(int /* a */, int /* b */) {
    throw Nhelper::MethodExecuteException("add Throw");
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("addAsync",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateAsyncWorker(info, add);
                }));

    exports.Set("concatAsync",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateAsyncWorker(info, concat);
                }));

    exports.Set("returnVoid",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateAsyncWorker(info, test);
                }));

    exports.Set("addThrow",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    return Nhelper::CreateAsyncWorker(info, addThrow);
                }));

    return exports;
}

NODE_API_MODULE(create_async_worker, InitAll);
