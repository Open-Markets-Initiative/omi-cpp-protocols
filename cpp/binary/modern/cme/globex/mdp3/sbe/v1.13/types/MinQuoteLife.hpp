#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Minimum Quote Life in number of microseconds
struct MinQuoteLife {

    static constexpr const char* name = "Min Quote Life";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MinQuoteLife()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinQuoteLife(const std::uint32_t value)
     : value{ value } {}

    // get value of MinQuoteLife field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
