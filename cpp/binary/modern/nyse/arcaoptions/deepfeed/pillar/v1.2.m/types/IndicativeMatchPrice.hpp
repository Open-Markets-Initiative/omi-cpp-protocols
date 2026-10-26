#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The price at which the highest number of contracts would trade, subject to auction collars.
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
