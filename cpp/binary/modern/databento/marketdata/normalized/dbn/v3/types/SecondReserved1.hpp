// Databento.MarketData.Normalized.Dbn.v3: types/SecondReserved1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// Reserved, 1 byte
struct SecondReserved1 {

    static constexpr auto name = "Second Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved1()
     : value{} {}

  protected:
    type value;
};
}
