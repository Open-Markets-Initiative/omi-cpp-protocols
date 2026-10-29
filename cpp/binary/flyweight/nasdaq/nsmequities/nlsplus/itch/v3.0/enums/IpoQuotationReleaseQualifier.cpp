#include "IpoQuotationReleaseQualifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(IpoQuotationReleaseQualifier value) {
    switch (value) {
        case IpoQuotationReleaseQualifier::Anticipated: return "Anticipated";
        case IpoQuotationReleaseQualifier::Cancelled: return "Cancelled";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoQuotationReleaseQualifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
