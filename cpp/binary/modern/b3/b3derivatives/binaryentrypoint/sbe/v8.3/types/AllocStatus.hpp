#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// allocStatus
struct AllocStatus {

    static constexpr auto name = "Alloc Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AllocStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocStatus(const char &value)
     : value{ value } {}

    // get value of AllocStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
