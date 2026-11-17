// Lseg.Millennium.Level2.Mitch.v11.9: types/Reserved1.hpp
#pragma once

#include <array>
#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reserved field
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved1()
     : value{} {}

  protected:
    type value;
};
}
