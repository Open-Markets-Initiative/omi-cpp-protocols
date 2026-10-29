#include "CrossType.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::NasdaqTexasOpeningCross: return "Nasdaq Texas Opening Cross";
        case CrossType::NasdaqTexasClosingCross: return "Nasdaq Texas Closing Cross";
        case CrossType::CrossForIpoAndHaltedPaused: return "Cross For Ipo And Halted Paused";
        case CrossType::NasdaqTexasCrossNetwork: return "Nasdaq Texas Cross Network";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
