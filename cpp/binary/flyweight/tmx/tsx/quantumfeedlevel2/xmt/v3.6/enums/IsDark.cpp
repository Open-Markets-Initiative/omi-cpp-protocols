// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/IsDark.cpp
#include "IsDark.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(IsDark value) {
    switch (value) {
        case IsDark::Yes: return "Yes";
        case IsDark::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsDark value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
