#include "MessageType.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::HeartbeatMessage: return "Heartbeat Message";
        case MessageType::SessionShutdownMessage: return "Session Shutdown Message";
        case MessageType::SequencedMessage: return "Sequenced Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
