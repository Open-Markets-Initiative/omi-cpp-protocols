#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// End date of a financing deal, i.e. the date the seller reimburses the buyer and takes back control of the collateral
struct EndDate {

    static constexpr const char* name = "End Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr EndDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EndDate(const std::uint16_t value)
     : value{ value } {}

    // get value of EndDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
