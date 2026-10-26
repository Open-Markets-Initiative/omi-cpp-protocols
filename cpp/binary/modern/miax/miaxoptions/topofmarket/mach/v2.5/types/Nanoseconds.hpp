#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Time at which this product is added/updated on MIAX system today.
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

    // get epoch nanoseconds: the stored base plus this field
    [[nodiscard]] std::int64_t get(const std::int64_t midnight_ns) const {
        return midnight_ns + static_cast<std::int64_t>(get());
    }

  protected:
    std::uint32_t value;
};
}
