#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// The price at which imbalances are calculated.
struct ReferencePrice {

    static constexpr const char* name = "Reference Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr ReferencePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferencePrice(const std::int32_t value)
     : value{ value } {}

    // get value of ReferencePrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
