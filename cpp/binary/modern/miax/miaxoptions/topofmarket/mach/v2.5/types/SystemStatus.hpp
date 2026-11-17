// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: types/SystemStatus.hpp
#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Current system status
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
