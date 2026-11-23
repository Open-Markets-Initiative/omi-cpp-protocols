// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/IsConditional.cpp
#include "IsConditional.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(IsConditional value) {
    switch (value) {
        case IsConditional::Yes: return "Yes";
        case IsConditional::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsConditional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
