#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Limit size that can’t be traded through
struct NttSize {

    static constexpr const char* name = "Ntt Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NttSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NttSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NttSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
