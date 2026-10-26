#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Identifier of the Order Book.
struct TradeableInstrumentId {

    static constexpr const char* name = "Tradeable Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeableInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeableInstrumentId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeableInstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
