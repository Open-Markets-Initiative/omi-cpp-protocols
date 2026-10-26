#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Unix time (seconds since 1970-01-01 00:00:00 UTC)
struct Seconds {

    static constexpr const char* name = "Seconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Seconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Seconds(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Seconds field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
