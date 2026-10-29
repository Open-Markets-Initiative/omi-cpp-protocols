#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Nanosecond offset from last unit timestamp
struct TimeOffset {

    static constexpr const char* name = "Time Offset";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TimeOffset()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeOffset(const std::uint32_t value)
     : value{ value } {}

    // get value of TimeOffset field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

    // get epoch nanoseconds: the stored base plus this field
    [[nodiscard]] std::int64_t get(const std::int64_t midnight_ns) const {
        return midnight_ns + static_cast<std::int64_t>(get());
    }

  protected:
    std::uint32_t value;
};
}
