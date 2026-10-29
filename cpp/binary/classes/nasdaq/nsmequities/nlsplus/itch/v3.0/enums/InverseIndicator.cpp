#include "InverseIndicator.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(InverseIndicator value) {
    switch (value) {
        case InverseIndicator::Inverse: return "Inverse";
        case InverseIndicator::NotInverse: return "Not Inverse";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InverseIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
