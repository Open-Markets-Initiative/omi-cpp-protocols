#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The indicative auction volume.
struct MatchedQuantity {

    static constexpr const char* name = "Matched Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MatchedQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchedQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MatchedQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
