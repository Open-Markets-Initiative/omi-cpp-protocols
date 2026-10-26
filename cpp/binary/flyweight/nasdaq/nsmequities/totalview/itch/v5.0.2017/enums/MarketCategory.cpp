#include "MarketCategory.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

std::string_view to_string(MarketCategory value) {
    switch (value) {
        case MarketCategory::NasdaqGlobalSelectMarket: return "Nasdaq Global Select Market";
        case MarketCategory::NasdaqGlobalMarket: return "Nasdaq Global Market";
        case MarketCategory::NasdaqCapitalMarket: return "Nasdaq Capital Market";
        case MarketCategory::Nyse: return "Nyse";
        case MarketCategory::NyseMkt: return "Nyse Mkt";
        case MarketCategory::NyseArca: return "Nyse Arca";
        case MarketCategory::BatsZ: return "Bats Z";
        case MarketCategory::InvestorsExchange: return "Investors Exchange";
        case MarketCategory::Na: return "Na";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
