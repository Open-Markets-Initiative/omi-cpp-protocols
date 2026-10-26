#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

// N/A. Populated with zero
struct IndicativePrice {

    static constexpr const char* name = "Indicative Price";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr IndicativePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndicativePrice(const std::uint64_t value)
     : value{ value } {}

    // get value of IndicativePrice field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
