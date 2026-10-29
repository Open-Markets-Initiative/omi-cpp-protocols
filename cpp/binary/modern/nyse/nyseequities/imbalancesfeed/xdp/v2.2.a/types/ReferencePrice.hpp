#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// See Information on Auctions for details
struct ReferencePrice {

    static constexpr const char* name = "Reference Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ReferencePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferencePrice(const std::uint32_t value)
     : value{ value } {}

    // get value of ReferencePrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
