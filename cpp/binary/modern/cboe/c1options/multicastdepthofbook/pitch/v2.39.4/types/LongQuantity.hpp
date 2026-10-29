#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Number of shares/contracts being added to the book (may be less than the number entered).
struct LongQuantity {

    static constexpr const char* name = "Long Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LongQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LongQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of LongQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
