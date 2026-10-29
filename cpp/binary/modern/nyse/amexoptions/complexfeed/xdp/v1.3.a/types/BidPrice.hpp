#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Best Bid price*. Should be used with the Price Scale Code from the Underlying Index Mapping message.
struct BidPrice {

    static constexpr const char* name = "Bid Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr BidPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidPrice(const std::int32_t value)
     : value{ value } {}

    // get value of BidPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
