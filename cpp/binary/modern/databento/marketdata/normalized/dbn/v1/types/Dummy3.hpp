#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved, 3 bytes
struct Dummy3 {

    static constexpr auto name = "Dummy 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Dummy3()
     : value{} {}

  protected:
    type value;
};
}
