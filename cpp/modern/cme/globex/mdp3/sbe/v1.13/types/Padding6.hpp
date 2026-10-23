#pragma once

#include <array>
#include <cstddef>

namespace cme::mdp3::v13 {


// 6 bytes padding
struct Padding6 {

    static constexpr auto name = "Padding 6";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding6()
     : value{} {}

  protected:
    type value;
};
}
