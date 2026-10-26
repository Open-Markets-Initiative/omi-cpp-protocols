#pragma once

#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Halt reason code
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct Reason {
    static constexpr std::string_view TradingHalt = "TH";            // Trading Halt
    static constexpr std::string_view RegulatoryHalt = "RH";         // Regulatory Halt
    static constexpr std::string_view MatchingHalt = "MH";           // Matching Halt
    static constexpr std::string_view TechnicalStop = "TS";          // Technical Stop
    static constexpr std::string_view TradingHaltKnockOut = "KO";    // Trading Halt Knock Out
    static constexpr std::string_view VolatilityHaltDynamic = "VHD"; // Volatility Halt Dynamic
    static constexpr std::string_view VolatilityHaltStatic = "VHS";  // Volatility Halt Static
    static constexpr std::string_view MarketMakerMissing = "MMM";    // Market Maker Missing
    static constexpr std::string_view UnderlyingNotQuoted = "UNQ";   // Underlying Not Quoted
    static constexpr std::string_view RestingMode = "RES";           // Resting Mode
    static constexpr std::string_view EarlyTermination = "ET";       // Early Termination
    static constexpr std::string_view ReasonNotAvailable = "    ";   // Reason Not Available

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == TradingHalt) { return "Trading Halt"; }
        if (code == RegulatoryHalt) { return "Regulatory Halt"; }
        if (code == MatchingHalt) { return "Matching Halt"; }
        if (code == TechnicalStop) { return "Technical Stop"; }
        if (code == TradingHaltKnockOut) { return "Trading Halt Knock Out"; }
        if (code == VolatilityHaltDynamic) { return "Volatility Halt Dynamic"; }
        if (code == VolatilityHaltStatic) { return "Volatility Halt Static"; }
        if (code == MarketMakerMissing) { return "Market Maker Missing"; }
        if (code == UnderlyingNotQuoted) { return "Underlying Not Quoted"; }
        if (code == RestingMode) { return "Resting Mode"; }
        if (code == EarlyTermination) { return "Early Termination"; }
        if (code == ReasonNotAvailable) { return "Reason Not Available"; }
        return {};
    }
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
