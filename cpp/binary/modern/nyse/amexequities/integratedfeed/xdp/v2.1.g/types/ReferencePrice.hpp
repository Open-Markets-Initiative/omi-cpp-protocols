#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// For Pillar-powered markets, the Reference Price is used to calculate the Indicative Match Price. For NYSE Tape A symbols, the Reference Price is the Last Sale if the last sale is at or between the current best quote.
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
