// Databento.MarketData.Normalized.Dbn.v3: types/LegIndex.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg index
struct LegIndex {

    static constexpr const char* name = "Leg Index";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr LegIndex()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegIndex(const std::uint16_t value)
     : value{ value } {}

    // get value of LegIndex field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
