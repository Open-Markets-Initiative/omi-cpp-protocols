#include "RetransmitMethod.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(RetransmitMethod value) {
    switch (value) {
        case RetransmitMethod::DeliverViaUdp: return "Deliver Via Udp";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetransmitMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
