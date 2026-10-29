#include "ExecuteUnderlyingTrade.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(ExecuteUnderlyingTrade value) {
    switch (value) {
        case ExecuteUnderlyingTrade::NoUnderlyingTrade: return "No Underlying Trade";
        case ExecuteUnderlyingTrade::UnderlyingOpposingTrade: return "Underlying Opposing Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExecuteUnderlyingTrade value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
