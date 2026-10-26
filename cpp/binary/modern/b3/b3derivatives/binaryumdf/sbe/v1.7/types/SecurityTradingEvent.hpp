#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// securityTradingEvent
struct SecurityTradingEvent {

    static constexpr auto name = "Security Trading Event";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr SecurityTradingEvent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityTradingEvent(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityTradingEvent field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
