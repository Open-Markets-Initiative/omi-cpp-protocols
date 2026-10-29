#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Reflects the current trading state for the strategy on the ISE market.
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
