#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Cumulative Buy contracts at the Reference Price and above.
struct BuyContracts {

    static constexpr const char* name = "Buy Contracts";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BuyContracts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyContracts(const std::uint32_t value)
     : value{ value } {}

    // get value of BuyContracts field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
