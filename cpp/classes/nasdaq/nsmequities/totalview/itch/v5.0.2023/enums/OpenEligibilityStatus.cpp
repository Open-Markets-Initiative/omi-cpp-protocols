#include "OpenEligibilityStatus.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(OpenEligibilityStatus value) {
    switch (value) {
        case OpenEligibilityStatus::NotEligible: return "Not Eligible";
        case OpenEligibilityStatus::Eligible: return "Eligible";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenEligibilityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
