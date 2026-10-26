#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Type of quote requested
struct QuoteType {

    static constexpr auto name = "Quote Type";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr QuoteType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteType(const std::int8_t &value)
     : value{ value } {}

    // get value of QuoteType field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
