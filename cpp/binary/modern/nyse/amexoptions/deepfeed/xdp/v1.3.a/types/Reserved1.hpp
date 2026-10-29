#pragma once

#include <array>
#include <cstddef>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {


// Filler
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
