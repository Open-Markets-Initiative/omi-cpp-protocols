#include "ParticipantId.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(ParticipantId value) {
    switch (value) {
        case ParticipantId::NyseAmericanLlcNyseAmerican: return "Nyse American Llc Nyse American";
        case ParticipantId::NasdaqOmxBxIncNasdaqOmxBx: return "Nasdaq Omx Bx Inc Nasdaq Omx Bx";
        case ParticipantId::NyseNationalIncNyseNational: return "Nyse National Inc Nyse National";
        case ParticipantId::FinraAlternativeDisplayFacilityAdf: return "Finra Alternative Display Facility Adf";
        case ParticipantId::TexasStockExchangeLlcTxse: return "Texas Stock Exchange Llc Txse";
        case ParticipantId::N24xNationalExchangeLlc24X: return "N24X National Exchange LLC 24X";
        case ParticipantId::MiaxPearlExchangeLlcMiax: return "Miax Pearl Exchange Llc Miax";
        case ParticipantId::InternationalSecuritiesExchangeLlcIse: return "International Securities Exchange Llc Ise";
        case ParticipantId::CboeEdgaExchangeIncCboeEdga: return "Cboe Edga Exchange Inc Cboe Edga";
        case ParticipantId::CboeEdgxExchangeIncCboeEdgx: return "Cboe Edgx Exchange Inc Cboe Edgx";
        case ParticipantId::LongTermStockExchangeIncLtse: return "Long Term Stock Exchange Inc Ltse";
        case ParticipantId::NyseTexasIncNyseTexas: return "Nyse Texas Inc Nyse Texas";
        case ParticipantId::NewYorkStockExchangeLlcNyse: return "New York Stock Exchange Llc Nyse";
        case ParticipantId::NyseArcaIncNyseArca: return "Nyse Arca Inc Nyse Arca";
        case ParticipantId::ConsolidatedTapeSystemCts: return "Consolidated Tape System Cts";
        case ParticipantId::NasdaqStockMarketLlcNasdaq: return "Nasdaq Stock Market Llc Nasdaq";
        case ParticipantId::MembersExchangeLlcMemx: return "Members Exchange Llc Memx";
        case ParticipantId::InvestorsExchangeLlcIex: return "Investors Exchange Llc Iex";
        case ParticipantId::CboeStockExchangeIncCbsx: return "Cboe Stock Exchange Inc Cbsx";
        case ParticipantId::NasdaqOmxPsxIncNasdaqOmxPsx: return "Nasdaq Omx Psx Inc Nasdaq Omx Psx";
        case ParticipantId::CboeByxExchangeIncCboeByx: return "Cboe Byx Exchange Inc Cboe Byx";
        case ParticipantId::CboeBzxExchangeIncCboeBzx: return "Cboe Bzx Exchange Inc Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
