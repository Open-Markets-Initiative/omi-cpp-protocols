#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Customer quantity on the bid side.
struct BidCustSize {

    static constexpr const char* name = "Bid Cust Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidCustSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidCustSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidCustSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
