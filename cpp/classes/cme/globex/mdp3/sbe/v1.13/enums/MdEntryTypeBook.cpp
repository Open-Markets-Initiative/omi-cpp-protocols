#include "MdEntryTypeBook.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(MdEntryTypeBook value) {
    switch (value) {
        case MdEntryTypeBook::Bid: return "Bid";
        case MdEntryTypeBook::Offer: return "Offer";
        case MdEntryTypeBook::ImpliedBid: return "Implied Bid";
        case MdEntryTypeBook::ImpliedOffer: return "Implied Offer";
        case MdEntryTypeBook::BookReset: return "Book Reset";
        case MdEntryTypeBook::MarketBestOffer: return "Market Best Offer";
        case MdEntryTypeBook::MarketBestBid: return "Market Best Bid";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryTypeBook value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cme::globex::mdp3::sbe::v1_13
