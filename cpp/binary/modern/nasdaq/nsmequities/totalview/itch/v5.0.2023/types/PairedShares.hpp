#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The total number of shares that are eligible to be matched at the Current Reference Price
struct PairedShares {

    static constexpr const char* name = "Paired Shares";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr PairedShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedShares(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of PairedShares field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
