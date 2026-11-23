// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/SellMinimumQuantity.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Minimum Quantity Of A Mutual Fund Required To Sell
struct SellMinimumQuantity {

    static constexpr const char* name = "Sell Minimum Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr SellMinimumQuantity()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit SellMinimumQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of SellMinimumQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
