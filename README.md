# node-addon-helper
Some tool functions simplify the development of node addon.

## Setup

### CMake.js

Add include directories to your CMakeLists.txt

```cmake
execute_process(COMMAND node -p "require('node-addon-helper').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_HELPER_DIR
        )

string(REPLACE "\n" "" NODE_ADDON_HELPER_DIR ${NODE_ADDON_HELPER_DIR})
string(REPLACE "\"" "" NODE_ADDON_HELPER_DIR ${NODE_ADDON_HELPER_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_HELPER_DIR})
```

## Usage

Look `./test/`  for all usage.

### TypeConveter

```c++
// test/type_converter.cpp

#include <nhelper/type_conveter.h>

template <typename T>
Napi::Value ExportConvertToT(const Napi::CallbackInfo& info) {
    return Nhelper::TypeConverter<T>::ToJSValue(
            info.Env(), Nhelper::TypeConverter<T>::ToNativeValue(info[0]));
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("convertBool",
                Napi::Function::New(env, ExportConvertToT<bool>));
}

```

```js
// test/type_converter.test.js
assert.equal(typeConverter.convertBool(true), true);
assert.equal(typeConverter.convertBool(false), false);
```

| c++                            | js                                  | predicate                           |
|--------------------------------|-------------------------------------|-------------------------------------|
| bool                           | Boolean                             | true/false                          |
| int8\_t                        | Number                              | INT8\_MIN - INT8\_MAX               |
| uint8\_t                       | Number                              | UINT8\_MIN - UINT8\_MAX             |
| int16\_t                       | Number                              | INT16\_MIN - INT16\_MAX             |
| uint16\_t                      | Number                              | UINT16\_MIN - UINT16\_MAX           |
| int32\_t                       | Number                              | INT32\_MIN - INT32\_MAX             |
| uint32\_t                      | Number                              | UINT32\_MIN - UINT32\_MAX           |
| int64\_t                       | Number                              | INT64\_MIN - INT64\_MAX             |
| float                          | Number                              |                                     |
| double                         | Number                              |                                     |
| std::string                    | Number                              |                                     |
| std::vector<T>                 | Array/ArrayBuffer/Buffer/TypedArray | T is integral and float\_point      |
| std::vector<T>                 | Array                               | T not is integral and float\_point  |
| std::pair<const char*, size_t> | ArrayBuffer/Buffer/TypedArray       | pointer of buffer's data and length |

### ArgsCheck
check info length
```c++
// test/args_check.cpp
#include "nhelper/args_check.h"
Napi::Value ExportCheckInfoLength(const Napi::CallbackInfo& info) {
    constexpr size_t length = 4;
    Nhelper::CheckInfoLength(info, length);
    return info.Env().Null();
}

```

check info's args type
```c++
// test/args_check.cpp
template <typename T>
Napi::Value ExportCheckInfoType(const Napi::CallbackInfo& info) {
    Nhelper::CheckInfoType<T>(info, 0);
    return info.Env().Null();
}

```
