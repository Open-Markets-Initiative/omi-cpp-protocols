#include "IpoFlag.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(IpoFlag value) {
    switch (value) {
        case IpoFlag::NewIpo: return "New Ipo";
        case IpoFlag::NotNewIpo: return "Not New Ipo";
        case IpoFlag::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
