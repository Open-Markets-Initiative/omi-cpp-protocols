#include "OpeningUnderlyingMarketCode.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(OpeningUnderlyingMarketCode value) {
    switch (value) {
        case OpeningUnderlyingMarketCode::NyseAmex: return "Nyse Amex";
        case OpeningUnderlyingMarketCode::NasdaqOmxBx: return "Nasdaq Omx Bx";
        case OpeningUnderlyingMarketCode::Nse: return "Nse";
        case OpeningUnderlyingMarketCode::FinraAdf: return "Finra Adf";
        case OpeningUnderlyingMarketCode::MarketIndependent: return "Market Independent";
        case OpeningUnderlyingMarketCode::Ise: return "Ise";
        case OpeningUnderlyingMarketCode::Edga: return "Edga";
        case OpeningUnderlyingMarketCode::Edgx: return "Edgx";
        case OpeningUnderlyingMarketCode::Cse: return "Cse";
        case OpeningUnderlyingMarketCode::NyseEuronext: return "Nyse Euronext";
        case OpeningUnderlyingMarketCode::NyseArca: return "Nyse Arca";
        case OpeningUnderlyingMarketCode::NasdaqOmxUtp: return "Nasdaq Omx Utp";
        case OpeningUnderlyingMarketCode::NasdaqOmxCta: return "Nasdaq Omx Cta";
        case OpeningUnderlyingMarketCode::Iex: return "Iex";
        case OpeningUnderlyingMarketCode::NasdaqOmxPhlx: return "Nasdaq Omx Phlx";
        case OpeningUnderlyingMarketCode::BatsY: return "Bats Y";
        case OpeningUnderlyingMarketCode::Bats: return "Bats";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpeningUnderlyingMarketCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
