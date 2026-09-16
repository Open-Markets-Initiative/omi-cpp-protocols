#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Identifier assigned per issue on an execution basis, unique and sequential each business day
struct MatchId {

    static constexpr const char* name = "Match Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MatchId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MatchId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
