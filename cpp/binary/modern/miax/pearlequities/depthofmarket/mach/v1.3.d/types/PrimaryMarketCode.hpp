#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Primary listing exchange code for the security.
struct PrimaryMarketCode {

    static constexpr auto name = "Primary Market Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PrimaryMarketCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrimaryMarketCode(const char &value)
     : value{ value } {}

    // get value of PrimaryMarketCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
