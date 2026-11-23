// Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80: types/Reserved5.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// Options Only. Reserved.
struct Reserved5 {

    static constexpr auto name = "Reserved 5";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved5()
     : value{} {}

  protected:
    type value;
};
}
