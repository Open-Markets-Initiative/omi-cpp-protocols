#include "TimeInForceOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(TimeInForceOptional value) {
    switch (value) {
        case TimeInForceOptional::Day: return "Day";
        case TimeInForceOptional::GoodTillCancel: return "Good Till Cancel";
        case TimeInForceOptional::ImmediateOrCancel: return "Immediate Or Cancel";
        case TimeInForceOptional::FillOrKill: return "Fill Or Kill";
        case TimeInForceOptional::GoodTillDate: return "Good Till Date";
        case TimeInForceOptional::AtTheClose: return "At The Close";
        case TimeInForceOptional::GoodForAuction: return "Good For Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TimeInForceOptional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
