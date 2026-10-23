#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Code to represent the type of event
struct EventType {

    static constexpr auto name = "Event Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr EventType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventType(const std::uint8_t &value)
     : value{ value } {}

    // get value of EventType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
