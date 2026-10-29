#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Market State
struct MarketState {

    static constexpr auto name = "Market State";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MarketState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketState(const std::uint8_t &value)
     : value{ value } {}

    // get value of MarketState field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
