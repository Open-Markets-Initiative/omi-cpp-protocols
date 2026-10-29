#include "SimpleOrdtype.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(SimpleOrdtype value) {
    switch (value) {
        case SimpleOrdtype::Market: return "Market";
        case SimpleOrdtype::Limit: return "Limit";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SimpleOrdtype value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
