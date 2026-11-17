// Siac.Cqs.Output.Cta.v2.10.a: types/Reserved62.hpp
#pragma once

#include <array>
#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Space-filled. Field is reserved for future use
struct Reserved62 {

    static constexpr auto name = "Reserved 62";
    static constexpr std::size_t size = 62;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved62()
     : value{} {}

  protected:
    type value;
};
}
