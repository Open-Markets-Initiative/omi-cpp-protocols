#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {

// Number of shares paired at the Reference Price using orders on the Auction Book
struct PairedShares {

    static constexpr const char* name = "Paired Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PairedShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedShares(const std::uint32_t value)
     : value{ value } {}

    // get value of PairedShares field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
