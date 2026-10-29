#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// maxFloor
struct MaxFloor {

    static constexpr const char* name = "Max Floor";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr MaxFloor()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaxFloor(const std::uint64_t value)
     : value{ value } {}

    // get value of MaxFloor field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
