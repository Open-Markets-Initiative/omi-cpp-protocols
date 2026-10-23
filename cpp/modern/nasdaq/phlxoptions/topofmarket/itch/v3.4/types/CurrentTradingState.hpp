#pragma once

#include <cstddef>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Reflects the current trading state for the option in the options market.
struct CurrentTradingState {

    static constexpr auto name = "Current Trading State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CurrentTradingState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CurrentTradingState(const char &value)
     : value{ value } {}

    // get value of CurrentTradingState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
