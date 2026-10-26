#pragma once

#include <cstddef>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Side of the leg
struct SideLeg {

    static constexpr auto name = "Side Leg";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SideLeg()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SideLeg(const char &value)
     : value{ value } {}

    // get value of SideLeg field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
