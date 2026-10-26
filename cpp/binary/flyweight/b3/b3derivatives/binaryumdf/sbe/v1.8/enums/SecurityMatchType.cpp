#include "SecurityMatchType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(SecurityMatchType value) {
    switch (value) {
        case SecurityMatchType::IssuingBuyBackAuction: return "Issuing Buy Back Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityMatchType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
