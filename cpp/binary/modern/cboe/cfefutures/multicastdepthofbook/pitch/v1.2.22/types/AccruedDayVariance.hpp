#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Accrued day variance as of the start of the trading day (signed 64-bit decimal with twelve implied decimal places).
struct AccruedDayVariance {

    static constexpr const char* name = "Accrued Day Variance";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 12;
    static constexpr double denominator = 1000000000000;
    using type = std::int64_t;

    // default constructor
    constexpr AccruedDayVariance()
     : value{ 0 } {}

    // constructor for AccruedDayVariance field
    constexpr explicit AccruedDayVariance(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AccruedDayVariance field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AccruedDayVariance field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
