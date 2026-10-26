#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Best ask price.
struct AskPrice4 {

    static constexpr const char* name = "Ask Price 4";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr AskPrice4()
     : value{ 0 } {}

    // constructor for AskPrice4 field
    constexpr explicit AskPrice4(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AskPrice4 field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AskPrice4 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
