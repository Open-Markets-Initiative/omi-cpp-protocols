#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The Dollar Value or Percentage Value used in the calculation of theTrading Collar
struct TradingCollarVariation {

    static constexpr const char* name = "Trading Collar Variation";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr TradingCollarVariation()
     : value{ 0 } {}

    // constructor for TradingCollarVariation field
    constexpr explicit TradingCollarVariation(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of TradingCollarVariation field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of TradingCollarVariation field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
