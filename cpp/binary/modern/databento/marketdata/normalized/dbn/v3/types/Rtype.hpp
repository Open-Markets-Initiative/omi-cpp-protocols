// Databento.MarketData.Normalized.Dbn.v3: types/Rtype.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The record type, which selects the record that follows the header
struct Rtype {

    static constexpr auto name = "Rtype";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Rtype()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Rtype(const std::uint8_t &value)
     : value{ value } {}

    // get value of Rtype field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
