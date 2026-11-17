// Databento.MarketData.Normalized.Dbn.v2: types/NumExtensions.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// Reserved for future use
struct NumExtensions {

    static constexpr auto name = "Num Extensions";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumExtensions()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumExtensions(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumExtensions field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
