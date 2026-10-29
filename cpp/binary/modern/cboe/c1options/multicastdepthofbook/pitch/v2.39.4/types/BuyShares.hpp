#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Number of shares on buy side at the Reference Price.
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
