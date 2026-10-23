#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Reflects the current trading state for the options security in the NASDAQ Options Market. The allowable values are:
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
