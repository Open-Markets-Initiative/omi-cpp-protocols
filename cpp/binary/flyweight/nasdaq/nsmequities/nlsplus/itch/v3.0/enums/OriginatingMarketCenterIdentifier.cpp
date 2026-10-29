#include "OriginatingMarketCenterIdentifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(OriginatingMarketCenterIdentifier value) {
    switch (value) {
        case OriginatingMarketCenterIdentifier::Nasdaq: return "Nasdaq";
        case OriginatingMarketCenterIdentifier::TrfCarteret: return "Trf Carteret";
        case OriginatingMarketCenterIdentifier::TrfChicago: return "Trf Chicago";
        case OriginatingMarketCenterIdentifier::Bx: return "Bx";
        case OriginatingMarketCenterIdentifier::Psx: return "Psx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OriginatingMarketCenterIdentifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
