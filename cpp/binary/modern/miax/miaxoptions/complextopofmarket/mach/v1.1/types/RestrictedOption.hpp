#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Restricted Option
struct RestrictedOption {

    static constexpr auto name = "Restricted Option";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RestrictedOption()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RestrictedOption(const char &value)
     : value{ value } {}

    // get value of RestrictedOption field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
