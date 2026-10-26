#include "CustomerFirmIndicator.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(CustomerFirmIndicator value) {
    switch (value) {
        case CustomerFirmIndicator::Customer: return "Customer";
        case CustomerFirmIndicator::FirmJoint: return "Firm Joint";
        case CustomerFirmIndicator::Onfloor: return "Onfloor";
        case CustomerFirmIndicator::Professional: return "Professional";
        case CustomerFirmIndicator::BrokerDealerNonRegistered: return "Broker Dealer Non Registered";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CustomerFirmIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
