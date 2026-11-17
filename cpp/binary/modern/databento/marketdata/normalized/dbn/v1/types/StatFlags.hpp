// Databento.MarketData.Normalized.Dbn.v1: types/StatFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// Additional flags associated with certain stat types
struct StatFlags {

    static constexpr auto name = "Stat Flags";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr StatFlags()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatFlags(const std::uint8_t &value)
     : value{ value } {}

    // get value of StatFlags field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
