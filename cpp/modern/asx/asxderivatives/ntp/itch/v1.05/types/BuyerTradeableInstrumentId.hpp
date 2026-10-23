#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Identifier of the Buyers Order Book.
struct BuyerTradeableInstrumentId {

    static constexpr const char* name = "Buyer Tradeable Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BuyerTradeableInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyerTradeableInstrumentId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BuyerTradeableInstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
