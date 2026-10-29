#include "Capacity.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(Capacity value) {
    switch (value) {
        case Capacity::Agency: return "Agency";
        case Capacity::Principal: return "Principal";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Capacity value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
