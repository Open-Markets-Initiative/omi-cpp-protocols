#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the daily established drop level value. Level 2 = 13% of Previous Close S&P 500 Value. Has implied 6 decimal places
struct MwcbLevel2 {

    static constexpr const char* name = "Mwcb Level 2";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr MwcbLevel2()
     : value{ 0 } {}

    // constructor for MwcbLevel2 field
    constexpr explicit MwcbLevel2(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of MwcbLevel2 field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of MwcbLevel2 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
