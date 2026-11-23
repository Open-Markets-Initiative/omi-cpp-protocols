// Databento.MarketData.Normalized.Dbn.v3: types/Reserved7.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


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
