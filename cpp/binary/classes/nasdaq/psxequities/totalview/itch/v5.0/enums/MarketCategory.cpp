#include "MarketCategory.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

std::string_view to_string(MarketCategory value) {
    switch (value) {
        case MarketCategory::NasdaqGlobalSelectMarket: return "Nasdaq Global Select Market";
        case MarketCategory::NasdaqGlobalMarket: return "Nasdaq Global Market";
        case MarketCategory::NasdaqCapitalMarket: return "Nasdaq Capital Market";
        case MarketCategory::Nyse: return "Nyse";
        case MarketCategory::NyseAmerican: return "Nyse American";
        case MarketCategory::NyseArca: return "Nyse Arca";
        case MarketCategory::BatsZ: return "Bats Z";
        case MarketCategory::NyseTexas: return "Nyse Texas";
        case MarketCategory::InvestorsExchangeLlc: return "Investors Exchange Llc";
        case MarketCategory::Na: return "Na";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::psxequities::totalview::itch::v5_0
