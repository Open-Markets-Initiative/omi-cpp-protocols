// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/StockState.hpp
#pragma once

#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The State Of The Stock
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct StockState {
    static constexpr std::string_view AuthorizedDelayed = "AR";              // Authorized Delayed
    static constexpr std::string_view InhibitedDelayed = "IR";               // Inhibited Delayed
    static constexpr std::string_view AuthorizedHalted = "AS";               // Authorized Halted
    static constexpr std::string_view InhibitedHalted = "IS";                // Inhibited Halted
    static constexpr std::string_view AuthorizedPriceMovementDelayed = "AE"; // Authorized Price Movement Delayed
    static constexpr std::string_view InhibitedPriceMovementDelayed = "IE";  // Inhibited Price Movement Delayed
    static constexpr std::string_view Authorized = "A";                      // Authorized
    static constexpr std::string_view Inhibited = "I";                       // Inhibited

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == AuthorizedDelayed) { return "Authorized Delayed"; }
        if (code == InhibitedDelayed) { return "Inhibited Delayed"; }
        if (code == AuthorizedHalted) { return "Authorized Halted"; }
        if (code == InhibitedHalted) { return "Inhibited Halted"; }
        if (code == AuthorizedPriceMovementDelayed) { return "Authorized Price Movement Delayed"; }
        if (code == InhibitedPriceMovementDelayed) { return "Inhibited Price Movement Delayed"; }
        if (code == Authorized) { return "Authorized"; }
        if (code == Inhibited) { return "Inhibited"; }
        return {};
    }
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
