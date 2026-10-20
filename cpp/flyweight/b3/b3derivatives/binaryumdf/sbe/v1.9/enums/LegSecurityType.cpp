#include "LegSecurityType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

std::string_view to_string(LegSecurityType value) {
    switch (value) {
        case LegSecurityType::Cash: return "Cash";
        case LegSecurityType::Corp: return "Corp";
        case LegSecurityType::Cs: return "Cs";
        case LegSecurityType::Dterm: return "Dterm";
        case LegSecurityType::Etf: return "Etf";
        case LegSecurityType::Fopt: return "Fopt";
        case LegSecurityType::Forward: return "Forward";
        case LegSecurityType::Fut: return "Fut";
        case LegSecurityType::Index: return "Index";
        case LegSecurityType::Indexopt: return "Indexopt";
        case LegSecurityType::Mleg: return "Mleg";
        case LegSecurityType::Opt: return "Opt";
        case LegSecurityType::Optexer: return "Optexer";
        case LegSecurityType::Ps: return "Ps";
        case LegSecurityType::Secloan: return "Secloan";
        case LegSecurityType::Sopt: return "Sopt";
        case LegSecurityType::Spot: return "Spot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
