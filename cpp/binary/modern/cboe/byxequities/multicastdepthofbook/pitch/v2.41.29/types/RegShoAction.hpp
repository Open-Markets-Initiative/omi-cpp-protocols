#pragma once

#include <cstddef>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {


// Reg SHO Action Values
struct RegShoAction {

    static constexpr auto name = "Reg Sho Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RegShoAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RegShoAction(const char &value)
     : value{ value } {}

    // get value of RegShoAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
