#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Trade flags. Bit 0 indicates SIP reportability; bit 1 indicates Retail Trade participation; bits 2-7 are reserved.
struct TradeFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Trade Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type SipReporting = 0x01;
        static const type RetailTradeIndicator = 0x02;
    };

    // default constructor
    constexpr TradeFlags()
     : value{ 0 } {}

    // 0 - Not reportable to the SIP; 1 - Reportable to the SIP.
    [[nodiscard]] constexpr bool SipReporting() const {
        return value & mask::SipReporting;
    }

    // 0 - Neither side is Retail; 1 - At least one side is Retail.
    [[nodiscard]] constexpr bool RetailTradeIndicator() const {
        return value & mask::RetailTradeIndicator;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
