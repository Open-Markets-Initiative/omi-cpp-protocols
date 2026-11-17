// Databento.MarketData.Normalized.Dbn.v1: types/MaturityYear.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The maturity year
struct MaturityYear {

    static constexpr const char* name = "Maturity Year";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MaturityYear()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityYear(const std::uint16_t value)
     : value{ value } {}

    // get value of MaturityYear field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
