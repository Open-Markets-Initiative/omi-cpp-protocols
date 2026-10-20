#include "EtpFlag.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(EtpFlag value) {
    switch (value) {
        case EtpFlag::Etp: return "Etp";
        case EtpFlag::NotEtp: return "Not Etp";
        case EtpFlag::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EtpFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
