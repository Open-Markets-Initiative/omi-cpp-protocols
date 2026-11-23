// Databento.MarketData.Normalized.Dbn.v3: types/Reserved18.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// Reserved, 18 bytes
struct Reserved18 {

    static constexpr auto name = "Reserved 18";
    static constexpr std::size_t size = 18;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved18()
     : value{} {}

  protected:
    type value;
};
}
