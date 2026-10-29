#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// ordStatus
struct OrdStatus {

    static constexpr auto name = "Ord Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrdStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrdStatus(const char &value)
     : value{ value } {}

    // get value of OrdStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
