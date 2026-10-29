#include "SecurityStatus.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::LightUpADarkSeries: return "Light Up A Dark Series";
        case SecurityStatus::OpenADarkSeries: return "Open A Dark Series";
        case SecurityStatus::Open: return "Open";
        case SecurityStatus::Close: return "Close";
        case SecurityStatus::Halt: return "Halt";
        case SecurityStatus::Unhalt: return "Unhalt";
        case SecurityStatus::UnhaltADarkSeries: return "Unhalt A Dark Series";
        case SecurityStatus::EndOfRfqAuction: return "End Of Rfq Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
