// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/MocEligible.cpp
#include "MocEligible.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(MocEligible value) {
    switch (value) {
        case MocEligible::Yes: return "Yes";
        case MocEligible::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MocEligible value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
