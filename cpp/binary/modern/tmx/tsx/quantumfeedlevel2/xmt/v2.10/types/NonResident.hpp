#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// A Terms Marker Indicating That Trade Participant Is Not A Canadian Resident
struct NonResident {

    static constexpr auto name = "Non Resident";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr NonResident()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NonResident(const char &value)
     : value{ value } {}

    // get value of NonResident field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
