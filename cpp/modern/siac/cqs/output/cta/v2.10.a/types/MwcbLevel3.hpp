#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies the daily established drop level value associated with Level 3 = 20% of Previous Close S&P 500 Value. Has implied 6 decimal places
struct MwcbLevel3 {

    static constexpr const char* name = "Mwcb Level 3";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr MwcbLevel3()
     : value{ 0 } {}

    // constructor for MwcbLevel3 field
    constexpr explicit MwcbLevel3(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of MwcbLevel3 field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of MwcbLevel3 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
