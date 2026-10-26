#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Nanoseconds since last message, accurate to the nearest microsecond.
struct Nanosecond {

    static constexpr const char* name = "Nanosecond";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Nanosecond()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Nanosecond(const std::uint32_t value)
     : value{ value } {}

    // get value of Nanosecond field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
