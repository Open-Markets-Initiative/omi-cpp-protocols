#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Cumulative Sell interest at the Indicative Price.
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
