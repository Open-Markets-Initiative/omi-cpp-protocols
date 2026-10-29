#include "SideOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(SideOptional value) {
    switch (value) {
        case SideOptional::Buy: return "Buy";
        case SideOptional::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SideOptional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
