#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Type Of Crosses Originating From A Participating Organization Between Managed Accounts That Have The Same Manager
struct CrossType {

    static constexpr auto name = "Cross Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CrossType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossType(const char &value)
     : value{ value } {}

    // get value of CrossType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
