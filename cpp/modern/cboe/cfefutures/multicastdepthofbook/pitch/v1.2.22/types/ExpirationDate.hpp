#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Expiration Date of Instrument.
struct ExpirationDate {

    static constexpr const char* name = "Expiration Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExpirationDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationDate(const std::uint32_t value)
     : value{ value } {}

    // get value of ExpirationDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
