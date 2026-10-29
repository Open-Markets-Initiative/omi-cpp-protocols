#include "QuoteStatusResponseTo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(QuoteStatusResponseTo value) {
    switch (value) {
        case QuoteStatusResponseTo::Quote: return "Quote";
        case QuoteStatusResponseTo::QuoteRequest: return "Quote Request";
        case QuoteStatusResponseTo::QuoteCancel: return "Quote Cancel";
        case QuoteStatusResponseTo::QuoteRequestReject: return "Quote Request Reject";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteStatusResponseTo value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
