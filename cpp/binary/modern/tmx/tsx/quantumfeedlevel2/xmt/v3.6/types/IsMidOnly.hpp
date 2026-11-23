// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/IsMidOnly.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Indicates A Dark Contra Midpoint Only Plus To Contra Midpoint Only Plus Execution
struct IsMidOnly {

    static constexpr auto name = "Is Mid Only";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IsMidOnly()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsMidOnly(const char &value)
     : value{ value } {}

    // get value of IsMidOnly field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
