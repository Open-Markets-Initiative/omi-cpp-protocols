#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The number of shares matched in the Nasdaq Cross
struct CrossShares {

    static constexpr const char* name = "Cross Shares";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CrossShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossShares(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of CrossShares field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
