#include "OpeningUnderlyingMarketCode.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(OpeningUnderlyingMarketCode value) {
    switch (value) {
        case OpeningUnderlyingMarketCode::NyseAmex: return "Nyse Amex";
        case OpeningUnderlyingMarketCode::NasdaqOmxBx: return "Nasdaq Omx Bx";
        case OpeningUnderlyingMarketCode::NationalStockExchange: return "National Stock Exchange";
        case OpeningUnderlyingMarketCode::FinraAdf: return "Finra Adf";
        case OpeningUnderlyingMarketCode::MarketIndependent: return "Market Independent";
        case OpeningUnderlyingMarketCode::MiaxPearlEquities: return "Miax Pearl Equities";
        case OpeningUnderlyingMarketCode::InternationalSecuritiesExchange: return "International Securities Exchange";
        case OpeningUnderlyingMarketCode::EdgaExchangeInc: return "Edga Exchange Inc";
        case OpeningUnderlyingMarketCode::EdgxExchangeInc: return "Edgx Exchange Inc";
        case OpeningUnderlyingMarketCode::Ltse: return "Ltse";
        case OpeningUnderlyingMarketCode::ChicagoStockExchange: return "Chicago Stock Exchange";
        case OpeningUnderlyingMarketCode::NyseEuronext: return "Nyse Euronext";
        case OpeningUnderlyingMarketCode::NyseArcaExchange: return "Nyse Arca Exchange";
        case OpeningUnderlyingMarketCode::NasdaqOmxUtp: return "Nasdaq Omx Utp";
        case OpeningUnderlyingMarketCode::NasdaqOmxCta: return "Nasdaq Omx Cta";
        case OpeningUnderlyingMarketCode::Memx: return "Memx";
        case OpeningUnderlyingMarketCode::Iex: return "Iex";
        case OpeningUnderlyingMarketCode::CboeStockExchange: return "Cboe Stock Exchange";
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

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
