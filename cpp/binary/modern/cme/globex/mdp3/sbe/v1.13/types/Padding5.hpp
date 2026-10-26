#pragma once

#include <array>
#include <cstddef>

namespace cme::mdp3::v13 {


// 5 bytes padding
struct Padding5 {

    static constexpr auto name = "Padding 5";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding5()
     : value{} {}

  protected:
    type value;
};
}
