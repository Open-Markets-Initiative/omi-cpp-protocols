#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::itch::v1_7 {


// Current trading state.
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
