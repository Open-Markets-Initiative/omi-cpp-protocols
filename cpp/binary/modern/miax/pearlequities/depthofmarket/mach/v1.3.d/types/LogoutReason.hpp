#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Logout Request Reason
struct LogoutReason {

    static constexpr auto name = "Logout Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LogoutReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LogoutReason(const char &value)
     : value{ value } {}

    // get value of LogoutReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
