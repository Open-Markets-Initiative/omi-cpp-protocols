#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The Nasdaq generated day-unique Match Number of this execution
struct MatchNumber {

    static constexpr const char* name = "Match Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MatchNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MatchNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
