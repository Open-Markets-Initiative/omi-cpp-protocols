#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Number of shares/contracts being added to the book (may be less than the number entered).
struct QuantityLong {

    static constexpr const char* name = "Quantity Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr QuantityLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuantityLong(const std::uint32_t value)
     : value{ value } {}

    // get value of QuantityLong field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
