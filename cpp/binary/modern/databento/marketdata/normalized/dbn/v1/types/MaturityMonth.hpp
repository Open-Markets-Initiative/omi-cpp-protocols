// Databento.MarketData.Normalized.Dbn.v1: types/MaturityMonth.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// The maturity month
struct MaturityMonth {

    static constexpr auto name = "Maturity Month";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MaturityMonth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityMonth(const std::uint8_t &value)
     : value{ value } {}

    // get value of MaturityMonth field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
