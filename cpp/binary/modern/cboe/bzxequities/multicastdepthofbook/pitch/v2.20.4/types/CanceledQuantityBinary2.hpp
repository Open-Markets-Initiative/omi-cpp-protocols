#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Number of shares/contracts
struct CanceledQuantityBinary2 {

    static constexpr const char* name = "Canceled Quantity Binary 2";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CanceledQuantityBinary2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledQuantityBinary2(const std::uint16_t value)
     : value{ value } {}

    // get value of CanceledQuantityBinary2 field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
