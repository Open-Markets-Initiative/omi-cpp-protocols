#include "AllocNoOrdersType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(AllocNoOrdersType value) {
    switch (value) {
        case AllocNoOrdersType::NotSpecified: return "Not Specified";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AllocNoOrdersType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
