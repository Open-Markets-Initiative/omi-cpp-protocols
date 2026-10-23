#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Start date of a financing deal, i.e. the date the buyer pays the seller cash and takes control of the collateral
struct StartDate {

    static constexpr const char* name = "Start Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr StartDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StartDate(const std::uint16_t value)
     : value{ value } {}

    // get value of StartDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
