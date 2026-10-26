#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Last Traded Price.
struct LastTrade {

    static constexpr const char* name = "Last Trade";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr LastTrade()
     : value{ 0 } {}

    // constructor for LastTrade field
    constexpr explicit LastTrade(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LastTrade field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LastTrade field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
