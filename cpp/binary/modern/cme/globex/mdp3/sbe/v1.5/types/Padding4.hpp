// Cme.Globex.Mdp3.Sbe.v1.5: types/Padding4.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


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
