#include "TradeType.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(TradeType value) {
    switch (value) {
        case TradeType::MainBook: return "Main Book";
        case TradeType::NordicMid: return "Nordic Mid";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
