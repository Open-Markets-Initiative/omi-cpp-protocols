// Databento.MarketData.Normalized.Dbn.v3: types/Reserved17.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// Reserved, 17 bytes
struct Reserved17 {

    static constexpr auto name = "Reserved 17";
    static constexpr std::size_t size = 17;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved17()
     : value{} {}

  protected:
    type value;
};
}
