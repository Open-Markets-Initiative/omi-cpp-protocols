#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates the current trading state for the stock
struct TradingState {

    static constexpr auto name = "Trading State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradingState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingState(const char &value)
     : value{ value } {}

    // get value of TradingState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
