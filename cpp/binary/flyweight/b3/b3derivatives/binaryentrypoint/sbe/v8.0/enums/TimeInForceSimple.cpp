#include "TimeInForceSimple.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(TimeInForceSimple value) {
    switch (value) {
        case TimeInForceSimple::Day: return "Day";
        case TimeInForceSimple::ImmediateOrCancel: return "Immediate Or Cancel";
        case TimeInForceSimple::FillOrKill: return "Fill Or Kill";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TimeInForceSimple value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
