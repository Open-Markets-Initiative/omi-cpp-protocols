#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// CorrectedPrice
struct CorrectedPrice {

    static constexpr const char* name = "Corrected Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr CorrectedPrice()
     : value{ 0 } {}

    // constructor for CorrectedPrice field
    constexpr explicit CorrectedPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of CorrectedPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of CorrectedPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
