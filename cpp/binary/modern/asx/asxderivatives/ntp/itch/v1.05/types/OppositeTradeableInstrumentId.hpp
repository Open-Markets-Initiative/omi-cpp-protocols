#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Identifier of the opposite Tradeable Instrument Id (references the combination Tradeable Instrument Id party to this trade).
struct OppositeTradeableInstrumentId {

    static constexpr const char* name = "Opposite Tradeable Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OppositeTradeableInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OppositeTradeableInstrumentId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OppositeTradeableInstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
