#include "IpoQuotationReleaseQualifier.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(IpoQuotationReleaseQualifier value) {
    switch (value) {
        case IpoQuotationReleaseQualifier::AnticipatedQuotationReleaseTime: return "Anticipated Quotation Release Time";
        case IpoQuotationReleaseQualifier::IpoReleaseCanceledOrPostponed: return "Ipo Release Canceled Or Postponed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoQuotationReleaseQualifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
