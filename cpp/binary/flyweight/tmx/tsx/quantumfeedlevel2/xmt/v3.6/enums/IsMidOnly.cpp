// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/IsMidOnly.cpp
#include "IsMidOnly.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(IsMidOnly value) {
    switch (value) {
        case IsMidOnly::Yes: return "Yes";
        case IsMidOnly::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsMidOnly value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
