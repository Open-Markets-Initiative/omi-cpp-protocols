#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// padding
struct Padding {

    static constexpr auto name = "Padding";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Padding()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Padding(const char &value)
     : value{ value } {}

    // get value of Padding field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
