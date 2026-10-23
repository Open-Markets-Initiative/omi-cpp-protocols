#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Identifies the current trading state of the instrument
struct MdSecurityTradingStatus {

    static constexpr auto name = "Md Security Trading Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MdSecurityTradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdSecurityTradingStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdSecurityTradingStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
