#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// allocNoOrdersType
struct AllocNoOrdersType {

    static constexpr auto name = "Alloc No Orders Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AllocNoOrdersType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocNoOrdersType(const char &value)
     : value{ value } {}

    // get value of AllocNoOrdersType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
