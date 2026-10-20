#include "SecurityType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(SecurityType value) {
    switch (value) {
        case SecurityType::Cash: return "Cash";
        case SecurityType::Corp: return "Corp";
        case SecurityType::Cs: return "Cs";
        case SecurityType::Dterm: return "Dterm";
        case SecurityType::Etf: return "Etf";
        case SecurityType::Fopt: return "Fopt";
        case SecurityType::Forward: return "Forward";
        case SecurityType::Fut: return "Fut";
        case SecurityType::Index: return "Index";
        case SecurityType::Indexopt: return "Indexopt";
        case SecurityType::Mleg: return "Mleg";
        case SecurityType::Opt: return "Opt";
        case SecurityType::Optexer: return "Optexer";
        case SecurityType::Ps: return "Ps";
        case SecurityType::Secloan: return "Secloan";
        case SecurityType::Sopt: return "Sopt";
        case SecurityType::Spot: return "Spot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
