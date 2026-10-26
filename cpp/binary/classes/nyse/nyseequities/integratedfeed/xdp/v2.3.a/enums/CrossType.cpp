#include "CrossType.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::MarketCenterEarlyOpeningAuction: return "Market Center Early Opening Auction";
        case CrossType::MarketCenterOpeningAuction: return "Market Center Opening Auction";
        case CrossType::MarketCenterReopeningAuction: return "Market Center Reopening Auction";
        case CrossType::MarketCenterClosingAuction: return "Market Center Closing Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
