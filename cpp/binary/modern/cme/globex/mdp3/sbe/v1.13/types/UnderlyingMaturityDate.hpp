#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Underlying Security's Maturity Date. Will be populated with Maturity Date of the underlying security instrument for Repo Specials only
struct UnderlyingMaturityDate {

    static constexpr const char* name = "Underlying Maturity Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr UnderlyingMaturityDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingMaturityDate(const std::uint16_t value)
     : value{ value } {}

    // get value of UnderlyingMaturityDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
