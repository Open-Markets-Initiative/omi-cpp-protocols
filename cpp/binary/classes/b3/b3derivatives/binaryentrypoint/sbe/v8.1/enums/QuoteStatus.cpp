#include "QuoteStatus.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(QuoteStatus value) {
    switch (value) {
        case QuoteStatus::Expired: return "Expired";
        case QuoteStatus::Accepted: return "Accepted";
        case QuoteStatus::Rejected: return "Rejected";
        case QuoteStatus::QuoteNotFound: return "Quote Not Found";
        case QuoteStatus::Pending: return "Pending";
        case QuoteStatus::Pass: return "Pass";
        case QuoteStatus::Canceled: return "Canceled";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
