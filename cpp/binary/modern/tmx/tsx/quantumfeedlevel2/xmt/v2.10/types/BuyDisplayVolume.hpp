#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Public Remaining Display Volume For The Buy Order
struct BuyDisplayVolume {

    static constexpr const char* name = "Buy Display Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr BuyDisplayVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyDisplayVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of BuyDisplayVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
