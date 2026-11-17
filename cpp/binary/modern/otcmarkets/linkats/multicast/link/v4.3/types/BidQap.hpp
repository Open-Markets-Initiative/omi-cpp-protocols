// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/BidQap.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Specifies the access fee or rebate for the bid. Positive values (1 to 30) indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates no rebate or access fee.
struct BidQap {

    static constexpr auto name = "Bid Qap";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr BidQap()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidQap(const std::int8_t &value)
     : value{ value } {}

    // get value of BidQap field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
