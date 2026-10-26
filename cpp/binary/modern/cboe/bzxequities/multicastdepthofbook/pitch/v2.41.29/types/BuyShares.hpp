#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

// Paired size of eligible periodic auction orders at the Reference Price
struct BuyShares {

    static constexpr const char* name = "Buy Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BuyShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyShares(const std::uint32_t value)
     : value{ value } {}

    // get value of BuyShares field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
