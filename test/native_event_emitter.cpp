#include "nhelper/native_event_emitter.h"

#include <thread>

#include "nhelper/native_event_transponder.h"

std::thread native_thread;

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set(
            "start",
            Napi::Function::New(env, [](const Napi::CallbackInfo& /* info */) {
                native_thread = std::thread([]() {
                    Nhelper::NativeEventEmitter<int32_t>::Emit("send_int32_t",
                                                               100);
                    Nhelper::NativeEventEmitter<double>::Emit("send_double",
                                                              100.1);
                    Nhelper::NativeEventEmitter<std::string>::Emit(
                            "send_string", "Hello JS");
                    Nhelper::NativeEventEmitter<std::vector<std::string>>::Emit(
                            "send_vector_string", {"Hello", "World"});
                });
            }));

    Nhelper::NativeEventTransponder<int32_t, double, std::string,
                                    std::vector<std::string>>::Init(env,
                                                                    exports);
    return exports;
}

NODE_API_MODULE(apiAsyncWorker, InitAll);
