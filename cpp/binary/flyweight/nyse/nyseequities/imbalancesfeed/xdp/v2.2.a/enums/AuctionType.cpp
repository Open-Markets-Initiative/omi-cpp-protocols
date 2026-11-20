// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a: enums/AuctionType.cpp
#include "AuctionType.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::EarlyOpening: return "Early Opening";
        case AuctionType::CoreOpening: return "Core Opening";
        case AuctionType::Reopening: return "Reopening";
        case AuctionType::Closing: return "Closing";
        case AuctionType::ExtremeClosingImbalance: return "Extreme Closing Imbalance";
        case AuctionType::RegulatoryClosingImbalance: return "Regulatory Closing Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
