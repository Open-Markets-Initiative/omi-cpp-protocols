#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Specifies price decimal precision for EBS instrument
struct PricePrecision {

    static constexpr auto name = "Price Precision";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PricePrecision()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PricePrecision(const std::uint8_t &value)
     : value{ value } {}

    // get value of PricePrecision field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
