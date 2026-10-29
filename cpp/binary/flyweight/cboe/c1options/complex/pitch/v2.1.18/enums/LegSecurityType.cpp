#include "LegSecurityType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(LegSecurityType value) {
    switch (value) {
        case LegSecurityType::Option: return "Option";
        case LegSecurityType::Equity: return "Equity";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
