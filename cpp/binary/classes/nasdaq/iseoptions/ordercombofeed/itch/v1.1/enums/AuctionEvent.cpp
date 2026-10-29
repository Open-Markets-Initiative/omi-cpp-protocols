#include "AuctionEvent.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(AuctionEvent value) {
    switch (value) {
        case AuctionEvent::Start: return "Start";
        case AuctionEvent::AuctionUpdate: return "Auction Update";
        case AuctionEvent::EndOfAuction: return "End Of Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
