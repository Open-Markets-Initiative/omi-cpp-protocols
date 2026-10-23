#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// "Y" = Far month expiration (as defined by MIAX rules), "N" = Near month expiration (as defined by MIAX rules)
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
