#include "DeliveryFlag.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::string_view to_string(DeliveryFlag value) {
    switch (value) {
        case DeliveryFlag::Heartbeat: return "Heartbeat";
        case DeliveryFlag::ContainsOriginalAndRefreshMsgs: return "Contains Original And Refresh Msgs";
        case DeliveryFlag::ContainsOnlyRefreshMessages: return "Contains Only Refresh Messages";
        case DeliveryFlag::XdpFailover: return "XDP Failover";
        case DeliveryFlag::ContainsOnlyOriginalMessages: return "Contains Only Original Messages";
        case DeliveryFlag::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, DeliveryFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
