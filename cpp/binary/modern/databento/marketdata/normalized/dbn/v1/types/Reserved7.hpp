#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved, 7 bytes
struct Reserved7 {

    static constexpr auto name = "Reserved 7";
    static constexpr std::size_t size = 7;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved7()
     : value{} {}

  protected:
    type value;
};
}
