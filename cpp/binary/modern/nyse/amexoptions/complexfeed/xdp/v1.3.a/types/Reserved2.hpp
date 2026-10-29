#pragma once

#include <array>
#include <cstddef>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {


// Filler
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
