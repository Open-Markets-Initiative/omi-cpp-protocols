#include "Side.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(Side value) {
    switch (value) {
        case Side::Bid: return "Bid";
        case Side::OfferAsk: return "Offer Ask";
        case Side::Hidden: return "Hidden";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Side value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
