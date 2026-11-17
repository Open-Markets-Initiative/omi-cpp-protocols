// Databento.MarketData.Normalized.Dbn.v1: types/MaturityDay.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// The maturity day
struct MaturityDay {

    static constexpr auto name = "Maturity Day";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MaturityDay()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityDay(const std::uint8_t &value)
     : value{ value } {}

    // get value of MaturityDay field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
