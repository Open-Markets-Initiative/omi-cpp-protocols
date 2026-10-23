#include "SipGeneratedMessageIdentifier.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(SipGeneratedMessageIdentifier value) {
    switch (value) {
        case SipGeneratedMessageIdentifier::SipGeneratedMessageNotApplicable: return "Sip Generated Message Not Applicable";
        case SipGeneratedMessageIdentifier::ConsolidatedQuotationSystem: return "Consolidated Quotation System";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SipGeneratedMessageIdentifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
