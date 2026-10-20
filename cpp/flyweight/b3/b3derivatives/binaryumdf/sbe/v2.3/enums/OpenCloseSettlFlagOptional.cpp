#include "OpenCloseSettlFlagOptional.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(OpenCloseSettlFlagOptional value) {
    switch (value) {
        case OpenCloseSettlFlagOptional::Daily: return "Daily";
        case OpenCloseSettlFlagOptional::Session: return "Session";
        case OpenCloseSettlFlagOptional::ExpectedEntry: return "Expected Entry";
        case OpenCloseSettlFlagOptional::EntryFromPreviousBusinessDay: return "Entry From Previous Business Day";
        case OpenCloseSettlFlagOptional::TheoreticalPrice: return "Theoretical Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenCloseSettlFlagOptional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
