#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// Used to identify the type of quantity.
struct PosType {

    static constexpr auto name = "Pos Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PosType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PosType(const char &value)
     : value{ value } {}

    // get value of PosType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
