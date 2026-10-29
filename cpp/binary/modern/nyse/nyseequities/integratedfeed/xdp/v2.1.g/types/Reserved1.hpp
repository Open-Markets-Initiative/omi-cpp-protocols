#pragma once

#include <array>
#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {


// This field is reserved for future use
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved1()
     : value{} {}

  protected:
    type value;
};
}
