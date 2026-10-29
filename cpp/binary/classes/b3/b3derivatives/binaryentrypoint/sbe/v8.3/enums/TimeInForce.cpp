#include "TimeInForce.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(TimeInForce value) {
    switch (value) {
        case TimeInForce::Day: return "Day";
        case TimeInForce::GoodTillCancel: return "Good Till Cancel";
        case TimeInForce::ImmediateOrCancel: return "Immediate Or Cancel";
        case TimeInForce::FillOrKill: return "Fill Or Kill";
        case TimeInForce::GoodTillDate: return "Good Till Date";
        case TimeInForce::AtTheClose: return "At The Close";
        case TimeInForce::GoodForAuction: return "Good For Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TimeInForce value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
