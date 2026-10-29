#include "IpoFlag.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

std::string_view to_string(IpoFlag value) {
    switch (value) {
        case IpoFlag::Yes: return "Yes";
        case IpoFlag::No: return "No";
        case IpoFlag::Na: return "Na";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IpoFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::psxequities::totalview::itch::v5_0
