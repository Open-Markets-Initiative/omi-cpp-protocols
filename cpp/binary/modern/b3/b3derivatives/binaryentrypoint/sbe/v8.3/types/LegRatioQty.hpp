#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// The ratio of quantity for this individual leg relative to the entire multileg security.
struct LegRatioQty {

    static constexpr const char* name = "Leg Ratio Qty";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 7;
    static constexpr double denominator = 10000000;
    using type = std::int64_t;

    // default constructor
    constexpr LegRatioQty()
     : value{ 0 } {}

    // constructor for LegRatioQty field
    constexpr explicit LegRatioQty(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LegRatioQty field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LegRatioQty field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
