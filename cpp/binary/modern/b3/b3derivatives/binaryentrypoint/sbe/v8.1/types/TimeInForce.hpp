#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// timeInForce
struct TimeInForce {

    static constexpr auto name = "Time In Force";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TimeInForce()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeInForce(const char &value)
     : value{ value } {}

    // get value of TimeInForce field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
