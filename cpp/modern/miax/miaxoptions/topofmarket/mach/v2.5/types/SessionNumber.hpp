#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// protocol packet type
struct SessionNumber {

    static constexpr auto name = "Session Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SessionNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of SessionNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
