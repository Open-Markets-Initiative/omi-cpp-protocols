#include "MarketId.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::string_view to_string(MarketId value) {
    switch (value) {
        case MarketId::NyseCash: return "Nyse Cash";
        case MarketId::EuropeCash: return "Europe Cash";
        case MarketId::NyseArcaCash: return "Nyse Arca Cash";
        case MarketId::NyseArcaOptions: return "Nyse Arca Options";
        case MarketId::NyseArcaBonds: return "Nyse Arca Bonds";
        case MarketId::ArcaEdge: return "Arca Edge";
        case MarketId::Liffe: return "Liffe";
        case MarketId::NyseAmericanOptions: return "Nyse American Options";
        case MarketId::NyseMktCash: return "Nyse Mkt Cash";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
