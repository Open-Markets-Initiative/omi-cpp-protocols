#include "AdministrativeMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(AdministrativeMessageType value) {
    switch (value) {
        case AdministrativeMessageType::Administrative: return "Administrative";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
