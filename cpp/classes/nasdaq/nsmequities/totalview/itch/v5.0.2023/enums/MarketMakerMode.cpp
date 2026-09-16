#include "MarketMakerMode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(MarketMakerMode value) {
    switch (value) {
        case MarketMakerMode::Normal: return "Normal";
        case MarketMakerMode::Passive: return "Passive";
        case MarketMakerMode::Syndicate: return "Syndicate";
        case MarketMakerMode::PreSyndicate: return "Pre Syndicate";
        case MarketMakerMode::Penalty: return "Penalty";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketMakerMode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
