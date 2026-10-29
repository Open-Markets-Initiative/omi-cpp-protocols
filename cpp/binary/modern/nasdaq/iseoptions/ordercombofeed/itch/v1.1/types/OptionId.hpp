#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// ISE’s Option ID for this leg, valid for the trading day. The same ID as the corresponding Option in the Options Directory Message. Zero (0) for Stock Leg.
struct OptionId {

    static constexpr const char* name = "Option Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OptionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OptionId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
