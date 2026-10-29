#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Public Remaining Volume For The Sell Order
struct SellDisplayVolume {

    static constexpr const char* name = "Sell Display Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr SellDisplayVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellDisplayVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of SellDisplayVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
