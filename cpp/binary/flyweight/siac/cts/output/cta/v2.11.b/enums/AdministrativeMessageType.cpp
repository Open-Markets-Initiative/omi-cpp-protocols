#include "AdministrativeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(AdministrativeMessageType value) {
    switch (value) {
        case AdministrativeMessageType::StartOfEndOfDaySummary: return "Start Of End Of Day Summary";
        case AdministrativeMessageType::EndOfEndOfDaySummary: return "End Of End Of Day Summary";
        case AdministrativeMessageType::StartOfStartOfDaySummary: return "Start Of Start Of Day Summary";
        case AdministrativeMessageType::EndOfStartOfDaySummary: return "End Of Start Of Day Summary";
        case AdministrativeMessageType::SymbolReferenceData: return "Symbol Reference Data";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
