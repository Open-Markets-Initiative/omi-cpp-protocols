#include "AdministrativeMessageType.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(AdministrativeMessageType value) {
    switch (value) {
        case AdministrativeMessageType::AdministrativeUnformattedMessage: return "Administrative Unformatted Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
