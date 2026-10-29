#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Public Numeric Identifier Assigned To A Sell Order By The Trading System
struct SellOrderId {

    static constexpr const char* name = "Sell Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr SellOrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellOrderId(const std::uint64_t value)
     : value{ value } {}

    // get value of SellOrderId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
