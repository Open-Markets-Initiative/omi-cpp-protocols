// Databento.MarketData.Normalized.Dbn.v2: types/Reserved2.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// Reserved, 2 bytes
struct Reserved2 {

    static constexpr auto name = "Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved2()
     : value{} {}

  protected:
    type value;
};
}
