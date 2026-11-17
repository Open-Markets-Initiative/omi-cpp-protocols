// Databento.MarketData.Normalized.Dbn.v2: types/Reserved10.hpp
#pragma once

#include <array>
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v2 {


// Reserved, 10 bytes
struct Reserved10 {

    static constexpr auto name = "Reserved 10";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved10()
     : value{} {}

  protected:
    type value;
};
}
