#include "AuctionType.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::Opening: return "Opening";
        case AuctionType::Reopening: return "Reopening";
        case AuctionType::PriceImprovement: return "Price Improvement";
        case AuctionType::Exposure: return "Exposure";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
