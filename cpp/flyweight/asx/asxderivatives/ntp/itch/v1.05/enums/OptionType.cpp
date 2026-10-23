#include "OptionType.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(OptionType value) {
    switch (value) {
        case OptionType::Put: return "Put";
        case OptionType::Call: return "Call";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OptionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
