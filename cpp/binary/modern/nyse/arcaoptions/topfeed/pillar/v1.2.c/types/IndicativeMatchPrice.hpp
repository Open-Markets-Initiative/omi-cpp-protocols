#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The price at which the highest number of contracts would trade, subject to auction collars. It includes the non-displayed quantity of Reserve Orders. See Information on Auctions for details.
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
