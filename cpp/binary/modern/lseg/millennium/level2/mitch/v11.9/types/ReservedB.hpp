// Lseg.Millennium.Level2.Mitch.v11.9: types/ReservedB.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reserved field
struct ReservedB {

    static constexpr auto name = "Reserved B";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr ReservedB()
     : value{} {}

  protected:
    type value;
};
}
