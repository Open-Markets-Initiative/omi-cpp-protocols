#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Cumulative Buy interest at the Indicative Price.
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
