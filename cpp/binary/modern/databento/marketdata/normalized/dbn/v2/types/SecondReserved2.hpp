// Databento.MarketData.Normalized.Dbn.v2: types/SecondReserved2.hpp
#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v2 {


// Reserved, 2 bytes
struct SecondReserved2 {

    static constexpr auto name = "Second Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved2()
     : value{} {}

  protected:
    type value;
};
}
