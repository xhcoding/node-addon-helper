#include "nhelper/module_raii.h"
#include <iostream>
int number = 0;

void init() {
    number = 1;
}

void deinit() {
    number = 0;
}

Napi::Value ExportGetValue(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), number);
}



Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    Nhelper::ModuleRAIIInit(env, exports, "_module_raii", init, deinit);
    exports.Set("getNumber", Napi::Function::New(env, ExportGetValue));
    return exports;
}

NODE_API_MODULE(type_converter, InitAll);
