#include "InverseIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(InverseIndicator value) {
    switch (value) {
        case InverseIndicator::InverseEtp: return "Inverse Etp";
        case InverseIndicator::NotInverseEtp: return "Not Inverse Etp";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InverseIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
