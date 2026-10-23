#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the Leverage ratio associated with the LULD Tier of the security symbol. Has implied 6 decimal places
struct LuldLeverageRatio {

    static constexpr const char* name = "Luld Leverage Ratio";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LuldLeverageRatio()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LuldLeverageRatio(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LuldLeverageRatio field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
