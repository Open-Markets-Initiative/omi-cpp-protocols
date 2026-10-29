#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Number of shares/contracts canceled
struct CanceledLongQuantity {

    static constexpr const char* name = "Canceled Long Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CanceledLongQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledLongQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of CanceledLongQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
