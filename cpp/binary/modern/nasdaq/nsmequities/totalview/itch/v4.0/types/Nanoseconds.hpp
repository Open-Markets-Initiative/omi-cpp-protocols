#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Nanoseconds portion of the timestamp.
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

    // get epoch nanoseconds: the stored base plus this field
    [[nodiscard]] std::int64_t get(const std::int64_t midnight_ns) const {
        return midnight_ns + static_cast<std::int64_t>(get());
    }

  protected:
    std::uint32_t value;
};
}
