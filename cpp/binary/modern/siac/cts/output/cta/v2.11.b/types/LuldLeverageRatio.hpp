#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the Leverage ratio associated with the LULD Tier of the security symbol. Has implied 6 decimal places
struct LuldLeverageRatio {

    static constexpr const char* name = "Luld Leverage Ratio";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint32_t;

    // default constructor
    constexpr LuldLeverageRatio()
     : value{ 0 } {}

    // constructor for LuldLeverageRatio field
    constexpr explicit LuldLeverageRatio(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LuldLeverageRatio field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LuldLeverageRatio field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
