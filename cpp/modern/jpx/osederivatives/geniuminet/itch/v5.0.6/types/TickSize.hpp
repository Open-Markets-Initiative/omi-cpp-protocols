#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Tick Size for the range
struct TickSize {

    static constexpr const char* name = "Tick Size";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TickSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TickSize(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of TickSize field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
