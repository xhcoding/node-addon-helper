#pragma once

#include <napi.h>

#include <tuple>

#include "type_converter.h"

namespace Nhelper {

template <size_t Idx, typename Tuple>
auto FetchInfoItem(const Napi::CallbackInfo& info) {
    return TypeConverter<std::tuple_element_t<Idx, Tuple>>::ToNativeValue(
            info[Idx]);
}

}  // namespace Nhelper
