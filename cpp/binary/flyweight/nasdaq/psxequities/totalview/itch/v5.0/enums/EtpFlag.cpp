#include "EtpFlag.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

std::string_view to_string(EtpFlag value) {
    switch (value) {
        case EtpFlag::Etp: return "Etp";
        case EtpFlag::NotEtp: return "Not Etp";
        case EtpFlag::Na: return "Na";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EtpFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::psxequities::totalview::itch::v5_0
