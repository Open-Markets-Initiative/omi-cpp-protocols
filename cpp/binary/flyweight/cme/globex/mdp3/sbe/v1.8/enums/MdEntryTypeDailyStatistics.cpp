#include "MdEntryTypeDailyStatistics.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

std::string_view to_string(MdEntryTypeDailyStatistics value) {
    switch (value) {
        case MdEntryTypeDailyStatistics::SettlementPrice: return "Settlement Price";
        case MdEntryTypeDailyStatistics::ClearedVolume: return "Cleared Volume";
        case MdEntryTypeDailyStatistics::OpenInterest: return "Open Interest";
        case MdEntryTypeDailyStatistics::FixingPrice: return "Fixing Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryTypeDailyStatistics value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cme::globex::mdp3::sbe::v1_8
