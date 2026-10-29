#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// ordType
struct SimpleOrdtype {

    static constexpr auto name = "Simple OrdType";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SimpleOrdtype()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SimpleOrdtype(const char &value)
     : value{ value } {}

    // get value of SimpleOrdtype field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
