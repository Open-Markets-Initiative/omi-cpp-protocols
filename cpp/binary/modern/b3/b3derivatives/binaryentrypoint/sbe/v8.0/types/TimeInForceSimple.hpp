#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// timeInForce
struct TimeInForceSimple {

    static constexpr auto name = "Time In Force Simple";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TimeInForceSimple()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeInForceSimple(const char &value)
     : value{ value } {}

    // get value of TimeInForceSimple field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
