#include "IpoFlag.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

std::string_view to_string(IpoFlag value) {
    switch (value) {
        case IpoFlag::SetUpForIpoRealease: return "Set Up For Ipo Realease";
        case IpoFlag::NotSetUpForIpoRealease: return "Not Set Up For Ipo Realease";
        case IpoFlag::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
