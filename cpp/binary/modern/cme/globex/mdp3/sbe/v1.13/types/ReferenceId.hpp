#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Reference to corresponding Price and Security ID, sequence of MD entry in the message
struct ReferenceId {

    static constexpr auto name = "Reference Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr ReferenceId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferenceId(const std::uint8_t &value)
     : value{ value } {}

    // get value of ReferenceId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
