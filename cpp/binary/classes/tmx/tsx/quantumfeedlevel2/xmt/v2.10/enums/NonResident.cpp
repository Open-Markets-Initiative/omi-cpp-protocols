// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/NonResident.cpp
#include "NonResident.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(NonResident value) {
    switch (value) {
        case NonResident::Yes: return "Yes";
        case NonResident::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, NonResident value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
