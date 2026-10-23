#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Login Status
struct LoginStatus {

    static constexpr auto name = "Login Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LoginStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LoginStatus(const char &value)
     : value{ value } {}

    // get value of LoginStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
