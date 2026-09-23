#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Set to UNIX time (seconds since 1970-01-01 00:00:00 UTC)
struct TimeSeconds {

    static constexpr const char* name = "Time Seconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TimeSeconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeSeconds(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TimeSeconds field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
