#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// allocTransType
struct AllocTransType {

    static constexpr auto name = "Alloc Trans Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AllocTransType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocTransType(const char &value)
     : value{ value } {}

    // get value of AllocTransType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
