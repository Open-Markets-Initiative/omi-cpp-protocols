// Siac.Cts.Output.Cta.v2.9: enums/AdministrativeMessageType.cpp
#include "AdministrativeMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(AdministrativeMessageType value) {
    switch (value) {
        case AdministrativeMessageType::StartOfEndOfDaySummaryMessage: return "Start Of End Of Day Summary Message";
        case AdministrativeMessageType::EndOfEndOfDaySummaryMessage: return "End Of End Of Day Summary Message";
        case AdministrativeMessageType::StartOfStartOfDaySummaryMessage: return "Start Of Start Of Day Summary Message";
        case AdministrativeMessageType::EndOfStartOfDaySummaryMessage: return "End Of Start Of Day Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
