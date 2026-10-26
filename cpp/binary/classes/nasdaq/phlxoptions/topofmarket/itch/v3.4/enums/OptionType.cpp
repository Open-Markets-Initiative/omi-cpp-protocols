#include "OptionType.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(OptionType value) {
    switch (value) {
        case OptionType::Call: return "Call";
        case OptionType::Put: return "Put";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OptionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
