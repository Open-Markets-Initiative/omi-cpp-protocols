#include "SecurityClass.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(SecurityClass value) {
    switch (value) {
        case SecurityClass::NasdaqListedIssue: return "Nasdaq Listed Issue";
        case SecurityClass::Nyse: return "Nyse";
        case SecurityClass::NyseAmerican: return "Nyse American";
        case SecurityClass::NyseArca: return "Nyse Arca";
        case SecurityClass::NyseTexas: return "Nyse Texas";
        case SecurityClass::Bats: return "Bats";
        case SecurityClass::Iexg: return "Iexg";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityClass value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
