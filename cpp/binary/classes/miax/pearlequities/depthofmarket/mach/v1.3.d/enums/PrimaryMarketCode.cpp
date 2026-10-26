#include "PrimaryMarketCode.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(PrimaryMarketCode value) {
    switch (value) {
        case PrimaryMarketCode::NyseAmerican: return "Nyse American";
        case PrimaryMarketCode::NasdaqTexas: return "Nasdaq Texas";
        case PrimaryMarketCode::NyseNational: return "Nyse National";
        case PrimaryMarketCode::TexasStockExchange: return "Texas Stock Exchange";
        case PrimaryMarketCode::N24xExchange: return "N24X Exchange";
        case PrimaryMarketCode::MiaxPearlEquities: return "Miax Pearl Equities";
        case PrimaryMarketCode::NasdaqIse: return "Nasdaq Ise";
        case PrimaryMarketCode::CboeEdgaExchange: return "Cboe Edga Exchange";
        case PrimaryMarketCode::CboeEdgxExchange: return "Cboe Edgx Exchange";
        case PrimaryMarketCode::LongTermStockExchange: return "Long Term Stock Exchange";
        case PrimaryMarketCode::NyseTexas: return "Nyse Texas";
        case PrimaryMarketCode::NewYorkStockExchange: return "New York Stock Exchange";
        case PrimaryMarketCode::NyseArca: return "Nyse Arca";
        case PrimaryMarketCode::Nasdaq: return "Nasdaq";
        case PrimaryMarketCode::MembersExchange: return "Members Exchange";
        case PrimaryMarketCode::InvestorsExchange: return "Investors Exchange";
        case PrimaryMarketCode::CboeStockExchange: return "Cboe Stock Exchange";
        case PrimaryMarketCode::NasdaqPhlx: return "Nasdaq Phlx";
        case PrimaryMarketCode::CboeByxExchange: return "Cboe Byx Exchange";
        case PrimaryMarketCode::CboeBzxExchange: return "Cboe Bzx Exchange";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrimaryMarketCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
