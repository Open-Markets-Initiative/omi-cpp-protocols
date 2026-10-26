#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Correction Number of the trade that was just corrected/adjusted. 0 for new trades.
struct ReferenceCorrectionNumber {

    static constexpr auto name = "Reference Correction Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ReferenceCorrectionNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferenceCorrectionNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of ReferenceCorrectionNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
