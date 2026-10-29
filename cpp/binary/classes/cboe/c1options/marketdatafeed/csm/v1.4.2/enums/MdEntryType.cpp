#include "MdEntryType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(MdEntryType value) {
    switch (value) {
        case MdEntryType::Bid: return "Bid";
        case MdEntryType::Ask: return "Ask";
        case MdEntryType::Trade: return "Trade";
        case MdEntryType::IndexValue: return "Index Value";
        case MdEntryType::OpeningPrice: return "Opening Price";
        case MdEntryType::SettlementValue: return "Settlement Value";
        case MdEntryType::High: return "High";
        case MdEntryType::Low: return "Low";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
