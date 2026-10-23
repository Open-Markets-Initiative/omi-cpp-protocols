#pragma once

#include <array>
#include <cstddef>

namespace cme::mdp3::v9 {


// 4 bytes padding
struct Padding4 {

    static constexpr auto name = "Padding 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding4()
     : value{} {}

  protected:
    type value;
};
}
