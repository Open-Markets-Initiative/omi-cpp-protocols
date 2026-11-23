// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/AckRequiredPossDup.cpp
#include "AckRequiredPossDup.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(AckRequiredPossDup value) {
    switch (value) {
        case AckRequiredPossDup::Unused: return "Unused";
        case AckRequiredPossDup::AckRequired: return "Ack Required";
        case AckRequiredPossDup::PossDup: return "Poss Dup";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AckRequiredPossDup value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
