// Lseg.Millennium.Level2.Mitch.v11.9: types/ReservedA.hpp
#pragma once

#include <array>
#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reserved field
struct ReservedA {

    static constexpr auto name = "Reserved A";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr ReservedA()
     : value{} {}

  protected:
    type value;
};
}
