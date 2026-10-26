#include "BestBidParticipantId.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(BestBidParticipantId value) {
    switch (value) {
        case BestBidParticipantId::NyseAmerican: return "Nyse American";
        case BestBidParticipantId::BostonOptionsExchange: return "Boston Options Exchange";
        case BestBidParticipantId::CboeOptionsExchange: return "Cboe Options Exchange";
        case BestBidParticipantId::MiaxEmerald: return "Miax Emerald";
        case BestBidParticipantId::CboeEdgxOptions: return "Cboe Edgx Options";
        case BestBidParticipantId::NasdaqGemx: return "Nasdaq Gemx";
        case BestBidParticipantId::NasdaqIse: return "Nasdaq Ise";
        case BestBidParticipantId::NasdaqMrx: return "Nasdaq Mrx";
        case BestBidParticipantId::MiamiInternationalSecuritiesExchange: return "Miami International Securities Exchange";
        case BestBidParticipantId::NyseArca: return "Nyse Arca";
        case BestBidParticipantId::OptionsPriceReportingAuthority: return "Options Price Reporting Authority";
        case BestBidParticipantId::MiaxPearl: return "Miax Pearl";
        case BestBidParticipantId::NasdaqOptionsMarket: return "Nasdaq Options Market";
        case BestBidParticipantId::NasdaqBxOptions: return "Nasdaq Bx Options";
        case BestBidParticipantId::CboeC2Options: return "Cboe C 2 Options";
        case BestBidParticipantId::NasdaqPhlx: return "Nasdaq Phlx";
        case BestBidParticipantId::CboeBzxOptionsExchange: return "Cboe Bzx Options Exchange";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BestBidParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
