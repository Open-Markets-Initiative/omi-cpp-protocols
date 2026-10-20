#include "OpenCloseSettlFlag.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

std::string_view to_string(OpenCloseSettlFlag value) {
    switch (value) {
        case OpenCloseSettlFlag::Daily: return "Daily";
        case OpenCloseSettlFlag::Session: return "Session";
        case OpenCloseSettlFlag::ExpectedEntry: return "Expected Entry";
        case OpenCloseSettlFlag::EntryFromPreviousBusinessDay: return "Entry From Previous Business Day";
        case OpenCloseSettlFlag::TheoreticalPrice: return "Theoretical Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenCloseSettlFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
