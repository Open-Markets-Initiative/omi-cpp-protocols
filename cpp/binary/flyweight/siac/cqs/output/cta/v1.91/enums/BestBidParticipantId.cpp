#include "BestBidParticipantId.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(BestBidParticipantId value) {
    switch (value) {
        case BestBidParticipantId::NyseAmerican: return "Nyse American";
        case BestBidParticipantId::NasdaqBx: return "Nasdaq Bx";
        case BestBidParticipantId::NyseNational: return "Nyse National";
        case BestBidParticipantId::FinraAdf: return "Finra Adf";
        case BestBidParticipantId::Ise: return "Ise";
        case BestBidParticipantId::CboeEdga: return "Cboe Edga";
        case BestBidParticipantId::CboeEdgx: return "Cboe Edgx";
        case BestBidParticipantId::Ltse: return "Ltse";
        case BestBidParticipantId::NyseChicago: return "Nyse Chicago";
        case BestBidParticipantId::Nyse: return "Nyse";
        case BestBidParticipantId::NyseArca: return "Nyse Arca";
        case BestBidParticipantId::Cqs: return "Cqs";
        case BestBidParticipantId::Nasdaq: return "Nasdaq";
        case BestBidParticipantId::Iex: return "Iex";
        case BestBidParticipantId::Cbsx: return "Cbsx";
        case BestBidParticipantId::NasdaqPsx: return "Nasdaq Psx";
        case BestBidParticipantId::CboeByx: return "Cboe Byx";
        case BestBidParticipantId::CboeBzx: return "Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BestBidParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
