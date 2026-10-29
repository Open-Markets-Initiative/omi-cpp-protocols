#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// contains the number of seconds from Epoch 1/1/1970, 00:00:00 UTC
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
