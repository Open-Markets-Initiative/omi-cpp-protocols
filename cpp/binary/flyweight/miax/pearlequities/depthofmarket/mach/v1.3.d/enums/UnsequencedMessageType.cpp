#include "UnsequencedMessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(UnsequencedMessageType value) {
    switch (value) {
        case UnsequencedMessageType::RefreshRequestMessage: return "Refresh Request Message";
        case UnsequencedMessageType::RefreshResponseMessage: return "Refresh Response Message";
        case UnsequencedMessageType::EndOfRefreshNotificationMessage: return "End Of Refresh Notification Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnsequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
