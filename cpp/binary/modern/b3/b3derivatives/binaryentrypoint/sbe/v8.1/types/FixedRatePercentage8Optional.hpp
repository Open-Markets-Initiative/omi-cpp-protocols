#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// fixedRate
struct FixedRatePercentage8Optional {

    static constexpr const char* name = "Fixed Rate Percentage 8 Optional";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr FixedRatePercentage8Optional()
     : value{ 0 } {}

    // constructor for FixedRatePercentage8Optional field
    constexpr explicit FixedRatePercentage8Optional(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of FixedRatePercentage8Optional field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of FixedRatePercentage8Optional field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
