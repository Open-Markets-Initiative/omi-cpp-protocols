#include "Display.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(Display value) {
    switch (value) {
        case Display::Unused: return "Unused";
        case Display::PostOnly: return "Post Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Display value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
