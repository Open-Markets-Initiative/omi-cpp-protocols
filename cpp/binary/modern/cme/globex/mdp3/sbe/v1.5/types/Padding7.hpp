#pragma once

#include <array>
#include <cstddef>

namespace cme::mdp3::v5 {


// 7 bytes padding
struct Padding7 {

    static constexpr auto name = "Padding 7";
    static constexpr std::size_t size = 7;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding7()
     : value{} {}

  protected:
    type value;
};
}
