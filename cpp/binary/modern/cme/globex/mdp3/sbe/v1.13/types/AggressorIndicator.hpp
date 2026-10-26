#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Aggressor Indicator 1=Aggressor Order 0=Passive Order
struct AggressorIndicator {

    static constexpr auto name = "Aggressor Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr AggressorIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AggressorIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of AggressorIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
