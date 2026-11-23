// Cme.Globex.Mdp3.Sbe.v1.13: types/Padding2.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// 2 bytes padding
struct Padding2 {

    static constexpr auto name = "Padding 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding2()
     : value{} {}

  protected:
    type value;
};
}
