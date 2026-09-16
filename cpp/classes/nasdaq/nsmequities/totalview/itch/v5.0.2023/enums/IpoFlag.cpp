#include "IpoFlag.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(IpoFlag value) {
    switch (value) {
        case IpoFlag::SetUpForIpoRelease: return "Set Up For Ipo Release";
        case IpoFlag::NotSetUpForIpoRelease: return "Not Set Up For Ipo Release";
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
