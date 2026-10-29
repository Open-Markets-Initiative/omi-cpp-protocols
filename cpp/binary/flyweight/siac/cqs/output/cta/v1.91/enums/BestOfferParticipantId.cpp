#include "BestOfferParticipantId.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(BestOfferParticipantId value) {
    switch (value) {
        case BestOfferParticipantId::NyseAmerican: return "Nyse American";
        case BestOfferParticipantId::NasdaqBx: return "Nasdaq Bx";
        case BestOfferParticipantId::NyseNational: return "Nyse National";
        case BestOfferParticipantId::FinraAdf: return "Finra Adf";
        case BestOfferParticipantId::Ise: return "Ise";
        case BestOfferParticipantId::CboeEdga: return "Cboe Edga";
        case BestOfferParticipantId::CboeEdgx: return "Cboe Edgx";
        case BestOfferParticipantId::Ltse: return "Ltse";
        case BestOfferParticipantId::NyseChicago: return "Nyse Chicago";
        case BestOfferParticipantId::Nyse: return "Nyse";
        case BestOfferParticipantId::NyseArca: return "Nyse Arca";
        case BestOfferParticipantId::Cqs: return "Cqs";
        case BestOfferParticipantId::Nasdaq: return "Nasdaq";
        case BestOfferParticipantId::Iex: return "Iex";
        case BestOfferParticipantId::Cbsx: return "Cbsx";
        case BestOfferParticipantId::NasdaqPsx: return "Nasdaq Psx";
        case BestOfferParticipantId::CboeByx: return "Cboe Byx";
        case BestOfferParticipantId::CboeBzx: return "Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BestOfferParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
