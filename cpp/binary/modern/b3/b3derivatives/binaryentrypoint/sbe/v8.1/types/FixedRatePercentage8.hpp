#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// fixedRate
struct FixedRatePercentage8 {

    static constexpr const char* name = "Fixed Rate Percentage 8";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr FixedRatePercentage8()
     : value{ 0 } {}

    // constructor for FixedRatePercentage8 field
    constexpr explicit FixedRatePercentage8(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of FixedRatePercentage8 field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of FixedRatePercentage8 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
