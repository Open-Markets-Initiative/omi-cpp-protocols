// Lseg.Millennium.Level2.Mitch.v11.9: types/ReservedByte.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reserved field
struct ReservedByte {

    static constexpr auto name = "Reserved Byte";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr ReservedByte()
     : value{} {}

  protected:
    type value;
};
}
