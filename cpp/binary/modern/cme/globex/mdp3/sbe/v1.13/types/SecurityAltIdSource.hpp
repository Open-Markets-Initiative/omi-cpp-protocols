#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Identifies class or source of the SecurityAltID (455) value
struct SecurityAltIdSource {

    static constexpr auto name = "Security Alt Id Source";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr SecurityAltIdSource()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityAltIdSource(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityAltIdSource field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
