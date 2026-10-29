#include "ReferenceForNetChange.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(ReferenceForNetChange value) {
    switch (value) {
        case ReferenceForNetChange::FirstTradePrice: return "First Trade Price";
        case ReferenceForNetChange::UnderwriterPrice: return "Underwriter Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ReferenceForNetChange value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
