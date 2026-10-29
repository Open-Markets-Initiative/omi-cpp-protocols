#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// BBO Collared auction price (see Auction Process Spec)
struct ReferencePrice {

    static constexpr const char* name = "Reference Price";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ReferencePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferencePrice(const std::uint64_t value)
     : value{ value } {}

    // get value of ReferencePrice field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
