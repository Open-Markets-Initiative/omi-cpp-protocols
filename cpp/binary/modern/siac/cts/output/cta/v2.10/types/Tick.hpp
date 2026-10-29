#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Represents for a Participant the upward, downward or unchanged price movement in a security's trades
struct Tick {

    static constexpr auto name = "Tick";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Tick()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Tick(const char &value)
     : value{ value } {}

    // get value of Tick field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
