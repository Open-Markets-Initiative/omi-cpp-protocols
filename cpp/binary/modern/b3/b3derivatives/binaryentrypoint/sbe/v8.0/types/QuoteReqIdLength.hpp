#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// 
struct QuoteReqIdLength {

    static constexpr auto name = "Quote Req Id Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr QuoteReqIdLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteReqIdLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of QuoteReqIdLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
