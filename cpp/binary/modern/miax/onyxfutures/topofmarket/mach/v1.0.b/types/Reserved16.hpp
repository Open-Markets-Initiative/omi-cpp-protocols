#pragma once

#include <array>
#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Reserved for future use
struct Reserved16 {

    static constexpr auto name = "Reserved 16";
    static constexpr std::size_t size = 16;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved16()
     : value{} {}

  protected:
    type value;
};
}
