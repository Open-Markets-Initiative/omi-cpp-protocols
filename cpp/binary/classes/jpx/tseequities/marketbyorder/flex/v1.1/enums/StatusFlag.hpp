#pragma once

#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates trading status
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct StatusFlag {
    static constexpr std::string_view TradingHaltedAcceptingOrders = "A0";    // Trading Halted Accepting Orders
    static constexpr std::string_view TradingHaltLifted = "A1";               // Trading Halt Lifted
    static constexpr std::string_view Itayose = "B0";                         // Itayose
    static constexpr std::string_view ItayoseEnded = "B1";                    // Itayose Ended
    static constexpr std::string_view TradingSuspended = "C0";                // Trading Suspended
    static constexpr std::string_view TradingSuspensionLifted = "C1";         // Trading Suspension Lifted
    static constexpr std::string_view TradingHaltedNotAcceptingOrders = "D0"; // Trading Halted Not Accepting Orders
    static constexpr std::string_view OtherThanTheAbove = "  ";               // Other Than The Above

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == TradingHaltedAcceptingOrders) { return "Trading Halted Accepting Orders"; }
        if (code == TradingHaltLifted) { return "Trading Halt Lifted"; }
        if (code == Itayose) { return "Itayose"; }
        if (code == ItayoseEnded) { return "Itayose Ended"; }
        if (code == TradingSuspended) { return "Trading Suspended"; }
        if (code == TradingSuspensionLifted) { return "Trading Suspension Lifted"; }
        if (code == TradingHaltedNotAcceptingOrders) { return "Trading Halted Not Accepting Orders"; }
        if (code == OtherThanTheAbove) { return "Other Than The Above"; }
        return {};
    }
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
