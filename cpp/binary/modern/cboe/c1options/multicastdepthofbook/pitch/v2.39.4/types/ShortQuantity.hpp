#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Number of shares/contracts being added to the book (may be less than the number entered).
struct ShortQuantity {

    static constexpr const char* name = "Short Quantity";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ShortQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortQuantity(const std::uint16_t value)
     : value{ value } {}

    // get value of ShortQuantity field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
