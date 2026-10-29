#include "AuctionType.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::EarlyOpening: return "Early Opening";
        case AuctionType::CoreOpening: return "Core Opening";
        case AuctionType::Reopening: return "Reopening";
        case AuctionType::Closing: return "Closing";
        case AuctionType::RegulatoryImbalance: return "Regulatory Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
