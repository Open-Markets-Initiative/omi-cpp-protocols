#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Indicates session date corresponding to the settlement price in tag 1150-TradingReferencePrice
struct TradingReferenceDate {

    static constexpr const char* name = "Trading Reference Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr TradingReferenceDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingReferenceDate(const std::uint16_t value)
     : value{ value } {}

    // get value of TradingReferenceDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
