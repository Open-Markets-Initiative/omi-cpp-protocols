#include "IpoQuotationReleaseQualifier.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(IpoQuotationReleaseQualifier value) {
    switch (value) {
        case IpoQuotationReleaseQualifier::AnticipatedQuotationReleaseTime: return "Anticipated Quotation Release Time";
        case IpoQuotationReleaseQualifier::IpoReleaseCanceledPostponed: return "Ipo Release Canceled Postponed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoQuotationReleaseQualifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
