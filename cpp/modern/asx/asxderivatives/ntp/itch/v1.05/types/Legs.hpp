#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Number of legs.
struct Legs {

    static constexpr auto name = "Legs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Legs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Legs(const std::uint8_t &value)
     : value{ value } {}

    // get value of Legs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
