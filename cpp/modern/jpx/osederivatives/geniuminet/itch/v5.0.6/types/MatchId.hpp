#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Assigned by the system to each match executed
struct MatchId {

    static constexpr const char* name = "Match Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MatchId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchId(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MatchId field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
