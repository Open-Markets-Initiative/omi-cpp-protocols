#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// fixedRate
struct FixedRate {

    static constexpr const char* name = "Fixed Rate";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr FixedRate()
     : value{ 0 } {}

    // constructor for FixedRate field
    constexpr explicit FixedRate(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of FixedRate field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of FixedRate field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
