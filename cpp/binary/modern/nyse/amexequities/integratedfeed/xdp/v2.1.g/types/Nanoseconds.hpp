#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The nanosecond offset from the Send Time
struct Nanoseconds {

    static constexpr const char* name = "Nanoseconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Nanoseconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Nanoseconds(const std::uint32_t value)
     : value{ value } {}

    // get value of Nanoseconds field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
