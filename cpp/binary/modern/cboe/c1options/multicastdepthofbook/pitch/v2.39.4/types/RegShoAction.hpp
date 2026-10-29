#pragma once

#include <cstddef>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


// 0, 1
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
