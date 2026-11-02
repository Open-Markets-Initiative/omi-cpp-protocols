#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved, 4 bytes
struct SecondReserved4 {

    static constexpr auto name = "Second Reserved 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved4()
     : value{} {}

  protected:
    type value;
};
}
