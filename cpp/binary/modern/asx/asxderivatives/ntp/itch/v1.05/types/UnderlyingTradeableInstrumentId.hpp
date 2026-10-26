#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Identifier of the Underlying Tradeable Instrument (can be zero if underlying not defined).
struct UnderlyingTradeableInstrumentId {

    static constexpr const char* name = "Underlying Tradeable Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnderlyingTradeableInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingTradeableInstrumentId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of UnderlyingTradeableInstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
