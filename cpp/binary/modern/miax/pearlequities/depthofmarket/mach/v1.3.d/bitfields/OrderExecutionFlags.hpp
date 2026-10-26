#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Order Execution flags. Bit 0 indicates SIP reportability; bit 1 indicates Traded Against Retail; bits 2-7 are reserved.
struct OrderExecutionFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Order Execution Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type SipReporting = 0x01;
        static const type TradedAgainstRetail = 0x02;
    };

    // default constructor
    constexpr OrderExecutionFlags()
     : value{ 0 } {}

    // 0 - Not reportable to the SIP; 1 - Reportable to the SIP.
    [[nodiscard]] constexpr bool SipReporting() const {
        return value & mask::SipReporting;
    }

    // 0 - Did not trade against Retail; 1 - Traded against Retail.
    [[nodiscard]] constexpr bool TradedAgainstRetail() const {
        return value & mask::TradedAgainstRetail;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
