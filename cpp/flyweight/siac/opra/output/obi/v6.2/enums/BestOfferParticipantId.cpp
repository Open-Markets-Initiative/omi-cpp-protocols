#include "BestOfferParticipantId.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(BestOfferParticipantId value) {
    switch (value) {
        case BestOfferParticipantId::NyseAmerican: return "Nyse American";
        case BestOfferParticipantId::BostonOptionsExchange: return "Boston Options Exchange";
        case BestOfferParticipantId::CboeOptionsExchange: return "Cboe Options Exchange";
        case BestOfferParticipantId::MiaxEmerald: return "Miax Emerald";
        case BestOfferParticipantId::CboeEdgxOptions: return "Cboe Edgx Options";
        case BestOfferParticipantId::NasdaqGemx: return "Nasdaq Gemx";
        case BestOfferParticipantId::NasdaqIse: return "Nasdaq Ise";
        case BestOfferParticipantId::NasdaqMrx: return "Nasdaq Mrx";
        case BestOfferParticipantId::MiamiInternationalSecuritiesExchange: return "Miami International Securities Exchange";
        case BestOfferParticipantId::NyseArca: return "Nyse Arca";
        case BestOfferParticipantId::OptionsPriceReportingAuthority: return "Options Price Reporting Authority";
        case BestOfferParticipantId::MiaxPearl: return "Miax Pearl";
        case BestOfferParticipantId::NasdaqOptionsMarket: return "Nasdaq Options Market";
        case BestOfferParticipantId::NasdaqBxOptions: return "Nasdaq Bx Options";
        case BestOfferParticipantId::CboeC2Options: return "Cboe C 2 Options";
        case BestOfferParticipantId::NasdaqPhlx: return "Nasdaq Phlx";
        case BestOfferParticipantId::CboeBzxOptionsExchange: return "Cboe Bzx Options Exchange";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BestOfferParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
