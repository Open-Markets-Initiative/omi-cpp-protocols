#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Customer professional quantity on the bid side.
struct BidProCustSize {

    static constexpr const char* name = "Bid Pro Cust Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidProCustSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidProCustSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidProCustSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
