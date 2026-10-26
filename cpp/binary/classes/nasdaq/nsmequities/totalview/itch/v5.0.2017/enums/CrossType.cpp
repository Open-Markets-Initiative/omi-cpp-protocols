#include "CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::OpeningCross: return "Opening Cross";
        case CrossType::ClosingCross: return "Closing Cross";
        case CrossType::CrossHaltedOrPaused: return "Cross Halted Or Paused";
        case CrossType::IntradayCrossAndPostCloseCross: return "Intraday Cross And Post Close Cross";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
