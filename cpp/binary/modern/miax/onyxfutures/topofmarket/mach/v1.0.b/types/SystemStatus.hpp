#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// System Status
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
