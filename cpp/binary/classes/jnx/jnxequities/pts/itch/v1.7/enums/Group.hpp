#pragma once

#include <string_view>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Orderbook group identifier.
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct Group {
    static constexpr std::string_view DaytimeMarket = "DAY";    // Daytime Market
    static constexpr std::string_view NighttimeMarket = "NGHT"; // Nighttime Market
    static constexpr std::string_view XMarket = "DAYX";         // X Market
    static constexpr std::string_view UMarket = "DAYU";         // U Market

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == DaytimeMarket) { return "Daytime Market"; }
        if (code == NighttimeMarket) { return "Nighttime Market"; }
        if (code == XMarket) { return "X Market"; }
        if (code == UMarket) { return "U Market"; }
        return {};
    }
};

} // namespace jnx::jnxequities::pts::itch::v1_7
