#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// The latest correction number of the given Trade id
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
