#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The total number of shares associated with the order being added to the book
struct Shares {

    static constexpr const char* name = "Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Shares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Shares(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Shares field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
