#include "SymbolCondition.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

std::string_view to_string(SymbolCondition value) {
    switch (value) {
        case SymbolCondition::Normal: return "Normal";
        case SymbolCondition::ClosingOnly: return "Closing Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SymbolCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
