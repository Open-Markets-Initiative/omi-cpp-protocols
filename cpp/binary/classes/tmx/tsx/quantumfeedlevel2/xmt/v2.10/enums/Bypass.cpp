// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/Bypass.cpp
#include "Bypass.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(Bypass value) {
    switch (value) {
        case Bypass::TheOrderIsABypass: return "The Order Is A Bypass";
        case Bypass::TheOrderIsNotABypass: return "The Order Is Not A Bypass";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Bypass value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
