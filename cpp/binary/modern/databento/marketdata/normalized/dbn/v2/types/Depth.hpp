// Databento.MarketData.Normalized.Dbn.v2: types/Depth.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The book level where the update event occurred
struct Depth {

    static constexpr auto name = "Depth";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Depth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Depth(const std::uint8_t &value)
     : value{ value } {}

    // get value of Depth field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
