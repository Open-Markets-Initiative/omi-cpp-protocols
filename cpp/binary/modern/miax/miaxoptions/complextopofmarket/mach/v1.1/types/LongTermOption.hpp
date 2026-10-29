#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Long Term Option
struct LongTermOption {

    static constexpr auto name = "Long Term Option";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LongTermOption()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LongTermOption(const char &value)
     : value{ value } {}

    // get value of LongTermOption field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
