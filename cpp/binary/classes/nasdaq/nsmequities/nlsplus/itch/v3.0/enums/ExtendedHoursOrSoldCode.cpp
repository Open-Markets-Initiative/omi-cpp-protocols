#include "ExtendedHoursOrSoldCode.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(ExtendedHoursOrSoldCode value) {
    switch (value) {
        case ExtendedHoursOrSoldCode::ExtendedHoursTrade: return "Extended Hours Trade";
        case ExtendedHoursOrSoldCode::ExtendedHoursTradeReportedLate: return "Extended Hours Trade Reported Late";
        case ExtendedHoursOrSoldCode::SoldLast: return "Sold Last";
        case ExtendedHoursOrSoldCode::SoldOutOfSequence: return "Sold Out Of Sequence";
        case ExtendedHoursOrSoldCode::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExtendedHoursOrSoldCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
