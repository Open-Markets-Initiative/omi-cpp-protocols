#pragma once

#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Exchange
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct Exchange {
    static constexpr std::string_view MiaxFuturesExchange = "XMGE"; // Miax Futures Exchange

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == MiaxFuturesExchange) { return "Miax Futures Exchange"; }
        return {};
    }
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
