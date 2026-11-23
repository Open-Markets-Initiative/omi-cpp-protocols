// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/IsDark.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Indicates The Passive Side Of The Trade Is Dark
struct IsDark {

    static constexpr auto name = "Is Dark";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IsDark()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsDark(const char &value)
     : value{ value } {}

    // get value of IsDark field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
