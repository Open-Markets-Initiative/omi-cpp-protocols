// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: types/FixedRate.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// fixedRate
struct FixedRate {

    static constexpr const char* name = "Fixed Rate";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
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
