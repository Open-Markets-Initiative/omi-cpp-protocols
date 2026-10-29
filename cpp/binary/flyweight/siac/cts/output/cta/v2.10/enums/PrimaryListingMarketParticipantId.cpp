#include "PrimaryListingMarketParticipantId.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(PrimaryListingMarketParticipantId value) {
    switch (value) {
        case PrimaryListingMarketParticipantId::NyseAmerican: return "Nyse American";
        case PrimaryListingMarketParticipantId::NasdaqBx: return "Nasdaq Bx";
        case PrimaryListingMarketParticipantId::NyseNational: return "Nyse National";
        case PrimaryListingMarketParticipantId::FinraAdf: return "Finra Adf";
        case PrimaryListingMarketParticipantId::Ise: return "Ise";
        case PrimaryListingMarketParticipantId::CboeEdga: return "Cboe Edga";
        case PrimaryListingMarketParticipantId::CboeEdgx: return "Cboe Edgx";
        case PrimaryListingMarketParticipantId::NyseChicago: return "Nyse Chicago";
        case PrimaryListingMarketParticipantId::Nyse: return "Nyse";
        case PrimaryListingMarketParticipantId::NyseArca: return "Nyse Arca";
        case PrimaryListingMarketParticipantId::Nasdaq: return "Nasdaq";
        case PrimaryListingMarketParticipantId::Iex: return "Iex";
        case PrimaryListingMarketParticipantId::Cbsx: return "Cbsx";
        case PrimaryListingMarketParticipantId::NasdaqPsx: return "Nasdaq Psx";
        case PrimaryListingMarketParticipantId::CboeByx: return "Cboe Byx";
        case PrimaryListingMarketParticipantId::CboeBzx: return "Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrimaryListingMarketParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
