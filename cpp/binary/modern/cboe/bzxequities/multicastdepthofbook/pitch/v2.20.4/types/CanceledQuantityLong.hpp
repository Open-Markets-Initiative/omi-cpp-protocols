// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4: types/CanceledQuantityLong.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Number of shares/contracts
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
