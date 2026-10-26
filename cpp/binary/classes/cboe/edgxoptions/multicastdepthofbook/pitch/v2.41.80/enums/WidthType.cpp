#include "WidthType.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

std::string_view to_string(WidthType value) {
    switch (value) {
        case WidthType::Regular: return "Regular";
        case WidthType::Volatility: return "Volatility";
        case WidthType::MaxQuoteWidth: return "Max Quote Width";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, WidthType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
