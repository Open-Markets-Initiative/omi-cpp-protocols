#include "IpoFlag.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(IpoFlag value) {
    switch (value) {
        case IpoFlag::IpoSecurity: return "Ipo Security";
        case IpoFlag::NotIpoSecurity: return "Not Ipo Security";
        case IpoFlag::NonIpoNewListedSecurity: return "Non Ipo New Listed Security";
        case IpoFlag::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
