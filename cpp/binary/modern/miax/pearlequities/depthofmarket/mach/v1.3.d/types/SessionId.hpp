#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Current trading session identifier.
struct SessionId {

    static constexpr auto name = "Session Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SessionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionId(const std::uint8_t &value)
     : value{ value } {}

    // get value of SessionId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
