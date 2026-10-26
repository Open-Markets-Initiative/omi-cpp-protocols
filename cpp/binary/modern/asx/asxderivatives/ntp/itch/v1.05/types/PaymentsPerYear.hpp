#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Number of payments per year for bonds.
struct PaymentsPerYear {

    static constexpr auto name = "Payments Per Year";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PaymentsPerYear()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PaymentsPerYear(const std::uint8_t &value)
     : value{ value } {}

    // get value of PaymentsPerYear field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
