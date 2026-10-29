#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// eventIndicator
struct EventIndicator {

    static constexpr auto name = "Event Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr EventIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of EventIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
