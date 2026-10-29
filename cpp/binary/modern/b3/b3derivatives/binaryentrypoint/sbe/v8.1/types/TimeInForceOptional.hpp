#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// timeInForce
struct TimeInForceOptional {

    static constexpr auto name = "Time In Force Optional";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr TimeInForceOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeInForceOptional(const char &value)
     : value{ value } {}

    // get value of TimeInForceOptional field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
