#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// price
struct Price8 {

    static constexpr const char* name = "Price 8";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr Price8()
     : value{ 0 } {}

    // constructor for Price8 field
    constexpr explicit Price8(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Price8 field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Price8 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
