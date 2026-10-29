#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// sendingTime
struct SendingTime {

    static constexpr auto name = "Sending Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr SendingTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SendingTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of SendingTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
