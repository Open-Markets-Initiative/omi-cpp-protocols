#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Current system status: “S” = Start of System hours “C” = End of System hours, “1” = Start of Test Session (sent before tests). “2” = End of Test Session.
struct SystemStatus {

    static constexpr auto name = "System Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SystemStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SystemStatus(const char &value)
     : value{ value } {}

    // get value of SystemStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
