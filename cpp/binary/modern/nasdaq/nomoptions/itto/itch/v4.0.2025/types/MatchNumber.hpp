#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Execution Id. Identifies the component of an execution. Unique for a given day. The match number is also referenced in the Trade Break Message.
struct MatchNumber {

    static constexpr const char* name = "Match Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MatchNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MatchNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
