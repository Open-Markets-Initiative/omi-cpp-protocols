#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// ordType
struct Ordtype {

    static constexpr auto name = "OrdType";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Ordtype()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Ordtype(const char &value)
     : value{ value } {}

    // get value of Ordtype field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
