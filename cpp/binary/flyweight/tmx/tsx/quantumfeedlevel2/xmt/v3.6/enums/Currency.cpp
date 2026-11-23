// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/Currency.cpp
#include "Currency.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(Currency value) {
    switch (value) {
        case Currency::Usd: return "Usd";
        case Currency::Cad: return "Cad";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Currency value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
