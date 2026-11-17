// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: enums/GoodbyeReason.cpp
#include "GoodbyeReason.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(GoodbyeReason value) {
    switch (value) {
        case GoodbyeReason::BadPacket: return "Bad Packet";
        case GoodbyeReason::TimedOut: return "Timed Out";
        case GoodbyeReason::ApplicationTerminatingConnection: return "Application Terminating Connection";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, GoodbyeReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
