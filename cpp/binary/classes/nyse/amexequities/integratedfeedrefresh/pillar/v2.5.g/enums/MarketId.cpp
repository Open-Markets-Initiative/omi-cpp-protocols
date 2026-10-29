#include "MarketId.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(MarketId value) {
    switch (value) {
        case MarketId::NyseEquities: return "Nyse Equities";
        case MarketId::NyseArcaEquities: return "Nyse Arca Equities";
        case MarketId::NyseArcaOptions: return "Nyse Arca Options";
        case MarketId::NyseBonds: return "Nyse Bonds";
        case MarketId::NyseAmericanOptions: return "Nyse American Options";
        case MarketId::NyseAmericanEquities: return "Nyse American Equities";
        case MarketId::NyseNationalEquities: return "Nyse National Equities";
        case MarketId::NyseTexasEquities: return "Nyse Texas Equities";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
