#pragma once

#include <cstddef>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Type of order
struct OppositeSide {

    static constexpr auto name = "Opposite Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OppositeSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OppositeSide(const char &value)
     : value{ value } {}

    // get value of OppositeSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
