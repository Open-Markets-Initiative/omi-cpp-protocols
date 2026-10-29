#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Indicates Which Side Began The Trade Correction
struct InitiatedBy {

    static constexpr auto name = "Initiated By";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InitiatedBy()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InitiatedBy(const char &value)
     : value{ value } {}

    // get value of InitiatedBy field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
