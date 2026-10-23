#pragma once

#include <array>
#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Reserved for future use.
struct SecondReserved8 {

    static constexpr auto name = "Second Reserved 8";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved8()
     : value{} {}

  protected:
    type value;
};
}
