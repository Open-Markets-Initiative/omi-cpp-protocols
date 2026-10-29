#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// quoteStatus
struct QuoteStatus {

    static constexpr auto name = "Quote Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr QuoteStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of QuoteStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
