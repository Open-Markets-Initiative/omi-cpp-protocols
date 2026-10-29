#include "EopType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(EopType value) {
    switch (value) {
        case EopType::Undefined: return "Undefined";
        case EopType::OpeningPrice: return "Opening Price";
        case EopType::NeedMoreSellers: return "Need More Sellers";
        case EopType::NeedMoreBuyers: return "Need More Buyers";
        case EopType::NoOpeningTrades: return "No Opening Trades";
        case EopType::MultipleOpeningPrices: return "Multiple Opening Prices";
        case EopType::NeedQuoteToOpen: return "Need Quote To Open";
        case EopType::PriceNotInQuoteRange: return "Price Not In Quote Range";
        case EopType::NeedDpmQuoteToOpen: return "Need Dpm Quote To Open";
        case EopType::DpmQuoteInvalid: return "Dpm Quote Invalid";
        case EopType::PriceNotInBotrRange: return "Price Not In Botr Range";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EopType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
