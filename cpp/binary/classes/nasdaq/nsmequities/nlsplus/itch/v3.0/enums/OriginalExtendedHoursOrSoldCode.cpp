#include "OriginalExtendedHoursOrSoldCode.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(OriginalExtendedHoursOrSoldCode value) {
    switch (value) {
        case OriginalExtendedHoursOrSoldCode::ExtendedHoursTrade: return "Extended Hours Trade";
        case OriginalExtendedHoursOrSoldCode::ExtendedHoursTradeReportedLate: return "Extended Hours Trade Reported Late";
        case OriginalExtendedHoursOrSoldCode::SoldLast: return "Sold Last";
        case OriginalExtendedHoursOrSoldCode::SoldOutOfSequence: return "Sold Out Of Sequence";
        case OriginalExtendedHoursOrSoldCode::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OriginalExtendedHoursOrSoldCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
