#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Unit timestamp expressed as number of whole seconds since the Epoch (Midnight, January 1, 1970 UTC).
struct UnitTimestamp {

    static constexpr const char* name = "Unit Timestamp";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnitTimestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnitTimestamp(const std::uint32_t value)
     : value{ value } {}

    // get value of UnitTimestamp field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
