#include "MarketCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(MarketCode value) {
    switch (value) {
        case MarketCode::Nasdaq: return "Nasdaq";
        case MarketCode::NasdaqTexas: return "Nasdaq Texas";
        case MarketCode::Psx: return "Psx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
