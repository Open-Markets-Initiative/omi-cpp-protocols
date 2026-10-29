#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// The best price at which the maximum volume of shares is executable in the applicable auction, subject to Auction Collars.
struct IndicativeMatchPrice {

    static constexpr const char* name = "Indicative Match Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr IndicativeMatchPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndicativeMatchPrice(const std::int32_t value)
     : value{ value } {}

    // get value of IndicativeMatchPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
