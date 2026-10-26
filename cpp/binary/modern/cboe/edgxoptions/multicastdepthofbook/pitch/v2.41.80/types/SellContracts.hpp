#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Cumulative Sell contracts at the Reference Price and below.
struct SellContracts {

    static constexpr const char* name = "Sell Contracts";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SellContracts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellContracts(const std::uint32_t value)
     : value{ value } {}

    // get value of SellContracts field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
