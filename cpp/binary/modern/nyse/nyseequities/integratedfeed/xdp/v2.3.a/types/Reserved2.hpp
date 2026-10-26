#pragma once

#include <array>
#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// Reserved for future use. Disregard any content.
struct Reserved2 {

    static constexpr auto name = "Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved2()
     : value{} {}

  protected:
    type value;
};
}
