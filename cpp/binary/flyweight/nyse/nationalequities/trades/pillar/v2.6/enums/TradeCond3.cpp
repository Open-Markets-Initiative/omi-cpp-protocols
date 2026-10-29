#include "TradeCond3.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(TradeCond3 value) {
    switch (value) {
        case TradeCond3::Na: return "Na";
        case TradeCond3::ExtendedHoursTrade: return "Extended Hours Trade";
        case TradeCond3::ExtendedHoursSoldOutOfSequence: return "Extended Hours Sold Out Of Sequence";
        case TradeCond3::Sold: return "Sold";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond3 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
