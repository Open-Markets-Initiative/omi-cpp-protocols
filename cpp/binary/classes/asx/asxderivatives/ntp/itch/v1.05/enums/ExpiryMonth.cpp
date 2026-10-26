#include "ExpiryMonth.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(ExpiryMonth value) {
    switch (value) {
        case ExpiryMonth::Jan: return "Jan";
        case ExpiryMonth::Feb: return "Feb";
        case ExpiryMonth::Mar: return "Mar";
        case ExpiryMonth::Apr: return "Apr";
        case ExpiryMonth::May: return "May";
        case ExpiryMonth::Jun: return "Jun";
        case ExpiryMonth::Jul: return "Jul";
        case ExpiryMonth::Aug: return "Aug";
        case ExpiryMonth::Sep: return "Sep";
        case ExpiryMonth::Oct: return "Oct";
        case ExpiryMonth::Nov: return "Nov";
        case ExpiryMonth::Dec: return "Dec";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExpiryMonth value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
