#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Unused
struct SessionState {

    static constexpr auto name = "Session State";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SessionState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionState(const std::uint8_t &value)
     : value{ value } {}

    // get value of SessionState field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
