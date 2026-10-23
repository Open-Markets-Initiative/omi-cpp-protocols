#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Identifier of the Seller’s Order Book.
struct SellerTradeableInstrumentId {

    static constexpr const char* name = "Seller Tradeable Instrument Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SellerTradeableInstrumentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellerTradeableInstrumentId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SellerTradeableInstrumentId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
