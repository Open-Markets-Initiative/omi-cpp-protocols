#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Time to the nearest microsecond
struct TimeMicroseconds {

    static constexpr const char* name = "Time Microseconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TimeMicroseconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeMicroseconds(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TimeMicroseconds field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

    // get epoch nanoseconds: the stored base plus this field
    [[nodiscard]] std::int64_t get(const std::int64_t midnight_ns) const {
        return midnight_ns + static_cast<std::int64_t>(get());
    }

  protected:
    std::uint32_t value;
};
}
