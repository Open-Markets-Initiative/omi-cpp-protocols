#include "MessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SnapshotRequestMessage: return "Snapshot Request Message";
        case MessageType::ErrorResponseMessage: return "Error Response Message";
        case MessageType::SnapshotStartMessage: return "Snapshot Start Message";
        case MessageType::SnapshotDataMessage: return "Snapshot Data Message";
        case MessageType::SnapshotEndMessage: return "Snapshot End Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::snap::v1_06
