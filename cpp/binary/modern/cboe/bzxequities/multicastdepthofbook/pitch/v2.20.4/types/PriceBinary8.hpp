#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Auction price
struct PriceBinary8 {

    static constexpr const char* name = "Price Binary 8";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr PriceBinary8()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceBinary8(const std::uint64_t value)
     : value{ value } {}

    // get value of PriceBinary8 field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
