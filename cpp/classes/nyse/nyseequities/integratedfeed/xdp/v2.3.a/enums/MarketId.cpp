#include "MarketId.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(MarketId value) {
    switch (value) {
        case MarketId::NyseEquities: return "Nyse Equities";
        case MarketId::NyseArcaEquities: return "Nyse Arca Equities";
        case MarketId::NyseArcaOptions: return "Nyse Arca Options";
        case MarketId::NyseBonds: return "Nyse Bonds";
        case MarketId::NyseAmexOptions: return "Nyse Amex Options";
        case MarketId::NyseAmericanEquities: return "Nyse American Equities";
        case MarketId::NyseNationalEquities: return "Nyse National Equities";
        case MarketId::NyseChicago: return "Nyse Chicago";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
