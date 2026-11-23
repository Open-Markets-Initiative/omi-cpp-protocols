// Databento.MarketData.Normalized.Dbn.v1: types/Reserved6.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved, 6 bytes
struct Reserved6 {

    static constexpr auto name = "Reserved 6";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved6()
     : value{} {}

  protected:
    type value;
};
}
