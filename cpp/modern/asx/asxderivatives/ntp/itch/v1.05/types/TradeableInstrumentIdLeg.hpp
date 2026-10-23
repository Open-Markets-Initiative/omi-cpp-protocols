#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Instrument Id of the leg
struct TradeableInstrumentIdLeg {

    static constexpr const char* name = "Tradeable Instrument Id Leg";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeableInstrumentIdLeg()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeableInstrumentIdLeg(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeableInstrumentIdLeg field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
