#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// MQL duration in number of microseconds applied to orders at AltMinPriceIncrement
struct AltMinQuoteLife {

    static constexpr const char* name = "Alt Min Quote Life";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 4294967295;

    // default constructor
    constexpr AltMinQuoteLife()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AltMinQuoteLife(const std::uint32_t value)
     : value{ value } {}

    // get value of AltMinQuoteLife field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
