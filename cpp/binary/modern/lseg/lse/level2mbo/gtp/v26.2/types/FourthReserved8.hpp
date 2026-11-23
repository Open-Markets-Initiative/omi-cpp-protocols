// Lseg.Lse.Level2Mbo.Gtp.v26.2: types/FourthReserved8.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Reserved for future use.
struct FourthReserved8 {

    static constexpr auto name = "Fourth Reserved 8";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr FourthReserved8()
     : value{} {}

  protected:
    type value;
};
}
