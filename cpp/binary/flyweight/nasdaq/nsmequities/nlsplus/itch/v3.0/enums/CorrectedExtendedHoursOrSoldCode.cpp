#include "CorrectedExtendedHoursOrSoldCode.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(CorrectedExtendedHoursOrSoldCode value) {
    switch (value) {
        case CorrectedExtendedHoursOrSoldCode::ExtendedHoursTrade: return "Extended Hours Trade";
        case CorrectedExtendedHoursOrSoldCode::ExtendedHoursTradeReportedLate: return "Extended Hours Trade Reported Late";
        case CorrectedExtendedHoursOrSoldCode::SoldLast: return "Sold Last";
        case CorrectedExtendedHoursOrSoldCode::SoldOutOfSequence: return "Sold Out Of Sequence";
        case CorrectedExtendedHoursOrSoldCode::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CorrectedExtendedHoursOrSoldCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
