#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The number of bid orders
struct BidCt {

    static constexpr const char* name = "Bid Ct";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidCt()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidCt(const std::uint32_t value)
     : value{ value } {}

    // get value of BidCt field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
