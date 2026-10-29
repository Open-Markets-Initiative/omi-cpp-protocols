#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// An Exchange Assigned Public Number Uniquely Identifying A Partici Pating Organization Associated With A Buy Order
struct BuyBrokerNumber {

    static constexpr const char* name = "Buy Broker Number";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr BuyBrokerNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyBrokerNumber(const std::uint16_t value)
     : value{ value } {}

    // get value of BuyBrokerNumber field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
