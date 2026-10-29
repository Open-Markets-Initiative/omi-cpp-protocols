#include "MarketCenter.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(MarketCenter value) {
    switch (value) {
        case MarketCenter::Nasdaq: return "Nasdaq";
        case MarketCenter::TrfCarteret: return "Trf Carteret";
        case MarketCenter::TrfChicago: return "Trf Chicago";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCenter value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
