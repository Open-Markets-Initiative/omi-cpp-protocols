#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Instrument quantity canceled
struct CanceledQuantity {

    static constexpr const char* name = "Canceled Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CanceledQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of CanceledQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
