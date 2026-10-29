#include "DeliveryFlag.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(DeliveryFlag value) {
    switch (value) {
        case DeliveryFlag::Heartbeat: return "Heartbeat";
        case DeliveryFlag::PillarFailover: return "Pillar Failover";
        case DeliveryFlag::OriginalMessage: return "Original Message";
        case DeliveryFlag::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case DeliveryFlag::OneRetransmissionPacket: return "One Retransmission Packet";
        case DeliveryFlag::RetransmissionSequenceMessage: return "Retransmission Sequence Message";
        case DeliveryFlag::OneRefreshPacket: return "One Refresh Packet";
        case DeliveryFlag::RefreshSequenceStart: return "Refresh Sequence Start";
        case DeliveryFlag::RefreshSequenceMessage: return "Refresh Sequence Message";
        case DeliveryFlag::RefreshSequenceEnd: return "Refresh Sequence End";
        case DeliveryFlag::MessageUnavailable: return "Message Unavailable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, DeliveryFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
