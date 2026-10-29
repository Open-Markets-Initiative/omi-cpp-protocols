#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Number of shares/contracts canceled
struct CanceledShortQuantity {

    static constexpr const char* name = "Canceled Short Quantity";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CanceledShortQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledShortQuantity(const std::uint16_t value)
     : value{ value } {}

    // get value of CanceledShortQuantity field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
