#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Indicates The Current Market State
struct MarketState {

    static constexpr auto name = "Market State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketState(const char &value)
     : value{ value } {}

    // get value of MarketState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
