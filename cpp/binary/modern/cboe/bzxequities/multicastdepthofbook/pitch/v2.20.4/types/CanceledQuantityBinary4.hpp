#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Number of shares/contracts
struct CanceledQuantityBinary4 {

    static constexpr const char* name = "Canceled Quantity Binary 4";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CanceledQuantityBinary4()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledQuantityBinary4(const std::uint32_t value)
     : value{ value } {}

    // get value of CanceledQuantityBinary4 field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
