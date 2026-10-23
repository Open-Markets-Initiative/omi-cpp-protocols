#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The total number of contracts that are eligible to be matched at the Current Reference Price. 0 for Price Improvement (PRISM) Auction.
struct PairedContracts {

    static constexpr const char* name = "Paired Contracts";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PairedContracts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedContracts(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PairedContracts field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
