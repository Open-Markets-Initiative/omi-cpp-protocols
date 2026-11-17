// Databento.MarketData.Normalized.Dbn.v2: types/MaturityWeek.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The maturity week
struct MaturityWeek {

    static constexpr auto name = "Maturity Week";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MaturityWeek()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityWeek(const std::uint8_t &value)
     : value{ value } {}

    // get value of MaturityWeek field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
