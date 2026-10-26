#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Highest Traded Price.
struct HighestTrade {

    static constexpr const char* name = "Highest Trade";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr HighestTrade()
     : value{ 0 } {}

    // constructor for HighestTrade field
    constexpr explicit HighestTrade(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of HighestTrade field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of HighestTrade field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
