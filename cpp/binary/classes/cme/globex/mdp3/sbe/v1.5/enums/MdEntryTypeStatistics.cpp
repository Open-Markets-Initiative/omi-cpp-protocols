#include "MdEntryTypeStatistics.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

std::string_view to_string(MdEntryTypeStatistics value) {
    switch (value) {
        case MdEntryTypeStatistics::OpenPrice: return "Open Price";
        case MdEntryTypeStatistics::HighTrade: return "High Trade";
        case MdEntryTypeStatistics::LowTrade: return "Low Trade";
        case MdEntryTypeStatistics::HighestBid: return "Highest Bid";
        case MdEntryTypeStatistics::LowestOffer: return "Lowest Offer";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryTypeStatistics value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cme::globex::mdp3::sbe::v1_5
