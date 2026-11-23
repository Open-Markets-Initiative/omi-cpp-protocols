// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: enums/SettlDateLocalMktDate32Optional.cpp
#include "SettlDateLocalMktDate32Optional.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(SettlDateLocalMktDate32Optional value) {
    switch (value) {
        case SettlDateLocalMktDate32Optional::NoEndDate: return "No End Date";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlDateLocalMktDate32Optional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
