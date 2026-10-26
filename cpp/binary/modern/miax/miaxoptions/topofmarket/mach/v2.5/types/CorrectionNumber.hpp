#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Trade correction number. 0 for New trades. Greater than or equal to 0 for trades resulting from corrections/adjustments.
struct CorrectionNumber {

    static constexpr auto name = "Correction Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CorrectionNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectionNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of CorrectionNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
