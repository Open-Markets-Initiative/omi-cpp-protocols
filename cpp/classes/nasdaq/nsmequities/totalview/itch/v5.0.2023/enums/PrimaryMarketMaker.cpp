#include "PrimaryMarketMaker.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(PrimaryMarketMaker value) {
    switch (value) {
        case PrimaryMarketMaker::Primary: return "Primary";
        case PrimaryMarketMaker::NonPrimary: return "Non Primary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrimaryMarketMaker value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
