#include "PrimaryMarketMaker.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(PrimaryMarketMaker value) {
    switch (value) {
        case PrimaryMarketMaker::PrimaryMarketMaker: return "Primary Market Maker";
        case PrimaryMarketMaker::NonPrimaryMarketMaker: return "Non Primary Market Maker";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrimaryMarketMaker value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
