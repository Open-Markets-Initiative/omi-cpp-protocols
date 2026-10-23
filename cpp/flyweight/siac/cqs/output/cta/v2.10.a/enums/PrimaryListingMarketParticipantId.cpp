#include "PrimaryListingMarketParticipantId.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(PrimaryListingMarketParticipantId value) {
    switch (value) {
        case PrimaryListingMarketParticipantId::PrimaryListingMarketParticipantIdNotApplicable: return "Primary Listing Market Participant Id Not Applicable";
        case PrimaryListingMarketParticipantId::NyseAmerican: return "Nyse American";
        case PrimaryListingMarketParticipantId::NasdaqOmxBx: return "Nasdaq Omx Bx";
        case PrimaryListingMarketParticipantId::NyseNational: return "Nyse National";
        case PrimaryListingMarketParticipantId::FinraAdf: return "Finra Adf";
        case PrimaryListingMarketParticipantId::N24x: return "N24X";
        case PrimaryListingMarketParticipantId::MiaxPearl: return "Miax Pearl";
        case PrimaryListingMarketParticipantId::Ise: return "Ise";
        case PrimaryListingMarketParticipantId::CboeEdga: return "Cboe Edga";
        case PrimaryListingMarketParticipantId::CboeEdgx: return "Cboe Edgx";
        case PrimaryListingMarketParticipantId::Ltse: return "Ltse";
        case PrimaryListingMarketParticipantId::NyseTexas: return "Nyse Texas";
        case PrimaryListingMarketParticipantId::Nyse: return "Nyse";
        case PrimaryListingMarketParticipantId::NyseArca: return "Nyse Arca";
        case PrimaryListingMarketParticipantId::Nasdaq: return "Nasdaq";
        case PrimaryListingMarketParticipantId::MembersExchange: return "Members Exchange";
        case PrimaryListingMarketParticipantId::Iex: return "Iex";
        case PrimaryListingMarketParticipantId::Cbsx: return "Cbsx";
        case PrimaryListingMarketParticipantId::NasdaqOmxPsx: return "Nasdaq Omx Psx";
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

} // namespace siac::cqs::output::cta::v2_10_a
