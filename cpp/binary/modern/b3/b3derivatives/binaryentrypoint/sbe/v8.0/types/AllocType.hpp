#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// allocType
struct AllocType {

    static constexpr auto name = "Alloc Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AllocType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocType(const char &value)
     : value{ value } {}

    // get value of AllocType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
