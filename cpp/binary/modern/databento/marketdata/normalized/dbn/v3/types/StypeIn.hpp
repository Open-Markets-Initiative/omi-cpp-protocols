// Databento.MarketData.Normalized.Dbn.v3: types/StypeIn.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The input symbology type
struct StypeIn {

    static constexpr auto name = "Stype In";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr StypeIn()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StypeIn(const std::uint8_t &value)
     : value{ value } {}

    // get value of StypeIn field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
