#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Lowest Traded Price.
struct LowestTrade {

    static constexpr const char* name = "Lowest Trade";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr LowestTrade()
     : value{ 0 } {}

    // constructor for LowestTrade field
    constexpr explicit LowestTrade(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LowestTrade field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LowestTrade field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
