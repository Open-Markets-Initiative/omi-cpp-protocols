#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// Reflects the current eligibility for auto execution of the options security in the options market.
struct OpenState {

    static constexpr auto name = "Open State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpenState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenState(const char &value)
     : value{ value } {}

    // get value of OpenState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
