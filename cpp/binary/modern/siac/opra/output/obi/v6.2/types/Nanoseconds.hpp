#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// the nanosecond portion of the time currently rounded to the nearest microsecond
struct Nanoseconds {

    static constexpr const char* name = "Nanoseconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Nanoseconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Nanoseconds(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Nanoseconds field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
