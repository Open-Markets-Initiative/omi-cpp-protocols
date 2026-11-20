// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/SourceId.cpp
#include "SourceId.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(SourceId value) {
    switch (value) {
        case SourceId::NonSourceRelated: return "Non Source Related";
        case SourceId::Tsx: return "TSX";
        case SourceId::TsxVenture: return "TSX Venture";
        case SourceId::Alpha: return "Alpha";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SourceId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
