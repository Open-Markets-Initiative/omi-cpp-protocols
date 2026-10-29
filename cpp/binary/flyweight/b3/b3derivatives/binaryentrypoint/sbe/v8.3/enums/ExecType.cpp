#include "ExecType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(ExecType value) {
    switch (value) {
        case ExecType::Trade: return "Trade";
        case ExecType::TradeCancel: return "Trade Cancel";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExecType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
