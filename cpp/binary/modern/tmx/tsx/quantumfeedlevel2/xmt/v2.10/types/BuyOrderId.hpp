#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Public Numeric Identifier Assigned To The Buy Order By The Trading System
struct BuyOrderId {

    static constexpr const char* name = "Buy Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr BuyOrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyOrderId(const std::uint64_t value)
     : value{ value } {}

    // get value of BuyOrderId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
