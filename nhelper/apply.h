#pragma once

#include <tuple>
#include <type_traits>

namespace Nhelper {

namespace details {

template <typename F, typename Tuple, std::size_t... Idx>
auto ApplyImpl(F f, const Tuple& t, std::index_sequence<Idx...>) {
    return f(std::get<Idx>(t)...);
}
}  // namespace details

template <typename F, typename Tuple>
auto Apply(F f, const Tuple& t) {
    return details::ApplyImpl(
            f, t, std::make_index_sequence<std::tuple_size<Tuple>::value>());
}

}  // namespace Nhelper
