#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Number of contracts canceled.
struct CanceledQuantityLong {

    static constexpr const char* name = "Canceled Quantity Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CanceledQuantityLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledQuantityLong(const std::uint32_t value)
     : value{ value } {}

    // get value of CanceledQuantityLong field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
