#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// For SPOT, number of business days between trade date and value (settlement) date. For NDF, number of business days between NDF valuation (fixing) and settlement
struct InterveningDays {

    static constexpr const char* name = "Intervening Days";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr InterveningDays()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InterveningDays(const std::uint16_t value)
     : value{ value } {}

    // get value of InterveningDays field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
