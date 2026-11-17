// Databento.MarketData.Normalized.Dbn.v2: types/FreezeStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// Reserved for future use
struct FreezeStatus {

    static constexpr auto name = "Freeze Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr FreezeStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FreezeStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of FreezeStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
