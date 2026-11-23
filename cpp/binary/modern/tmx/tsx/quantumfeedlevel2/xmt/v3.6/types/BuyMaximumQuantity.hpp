// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/BuyMaximumQuantity.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Maximum Quantity Of A Mutual Fund Allowed To Purchase
struct BuyMaximumQuantity {

    static constexpr const char* name = "Buy Maximum Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr BuyMaximumQuantity()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit BuyMaximumQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of BuyMaximumQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
