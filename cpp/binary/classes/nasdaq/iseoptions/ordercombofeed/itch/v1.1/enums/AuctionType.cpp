#include "AuctionType.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::Exposure: return "Exposure";
        case AuctionType::Facilitation: return "Facilitation";
        case AuctionType::Solicitation: return "Solicitation";
        case AuctionType::Pim: return "Pim";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
