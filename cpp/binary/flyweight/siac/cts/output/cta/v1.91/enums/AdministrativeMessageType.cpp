#include "AdministrativeMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(AdministrativeMessageType value) {
    switch (value) {
        case AdministrativeMessageType::StartOfEndOfDayMessage: return "Start Of End Of Day Message";
        case AdministrativeMessageType::EndOfEndOfDayMessage: return "End Of End Of Day Message";
        case AdministrativeMessageType::StartOfStartOfDayMessage: return "Start Of Start Of Day Message";
        case AdministrativeMessageType::EndOfStartOfDayMessage: return "End Of Start Of Day Message";
        case AdministrativeMessageType::AdministrativeUnformattedMessage: return "Administrative Unformatted Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
