#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// An Exchange Assigned Number Uniquely Identifying A Partici Pating Organization Associated With A Sell Order
struct SellBrokerNumber {

    static constexpr const char* name = "Sell Broker Number";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr SellBrokerNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellBrokerNumber(const std::uint16_t value)
     : value{ value } {}

    // get value of SellBrokerNumber field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
