#include "CrossType.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::OpeningCross: return "Opening Cross";
        case CrossType::ScheduledIntradayCross: return "Scheduled Intraday Cross";
        case CrossType::ClosingCross: return "Closing Cross";
        case CrossType::CrossForHaltedSecurities: return "Cross For Halted Securities";
        case CrossType::AuctionOnDemand: return "Auction On Demand";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
