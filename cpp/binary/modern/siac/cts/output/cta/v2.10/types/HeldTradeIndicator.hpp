#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// The Held Trade Indicator reflects whether this trade qualifies for the Participant or Consolidated Last Price at the time it is disseminated
struct HeldTradeIndicator {

    static constexpr auto name = "Held Trade Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr HeldTradeIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HeldTradeIndicator(const char &value)
     : value{ value } {}

    // get value of HeldTradeIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
