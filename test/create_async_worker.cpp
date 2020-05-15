#include "nhelper/create_async_worker.h"

int add(int a, int b) {
    return a + b;
}

void test(const std::string& message, double b) {

}

std::string concat(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("addAsync",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    Nhelper::CreateAsyncWorker(info, add)
                            .SetOKHandler([](Napi::Env& env,
                                             Napi::FunctionReference& callback,
                                             const int& sum) {
                                callback.Call({Napi::Number::New(env, sum)});
                            })
                            .Queue();
                }));

        exports.Set("concatAsync",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    Nhelper::CreateAsyncWorker(info, concat)
                            .SetOKHandler([](Napi::Env& env,
                                             Napi::FunctionReference& callback,
                                             const std::string& sum) {
                                callback.Call({Napi::String::New(env, sum)});
                            })
                            .Queue();
                }));


    exports.Set("returnVoid",
                Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
                    Nhelper::CreateAsyncWorker(info, test)
                            .SetOKHandler([](Napi::Env& env,
                                             Napi::FunctionReference& callback) {
                                callback.Call({Napi::String::New(env, "returnVoid")});
                            })
                            .Queue();
                }));


    return exports;
}

NODE_API_MODULE(create_async_worker, InitAll);
