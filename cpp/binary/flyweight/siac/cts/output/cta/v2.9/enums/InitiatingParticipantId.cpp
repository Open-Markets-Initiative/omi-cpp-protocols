#include "InitiatingParticipantId.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(InitiatingParticipantId value) {
    switch (value) {
        case InitiatingParticipantId::NyseAmerican: return "Nyse American";
        case InitiatingParticipantId::NasdaqBx: return "Nasdaq Bx";
        case InitiatingParticipantId::NyseNational: return "Nyse National";
        case InitiatingParticipantId::Adf: return "Adf";
        case InitiatingParticipantId::Miax: return "Miax";
        case InitiatingParticipantId::Ise: return "Ise";
        case InitiatingParticipantId::CboeEdga: return "Cboe Edga";
        case InitiatingParticipantId::CboeEdgx: return "Cboe Edgx";
        case InitiatingParticipantId::Ltse: return "Ltse";
        case InitiatingParticipantId::NyseChicago: return "Nyse Chicago";
        case InitiatingParticipantId::Nyse: return "Nyse";
        case InitiatingParticipantId::NyseArca: return "Nyse Arca";
        case InitiatingParticipantId::Cts: return "Cts";
        case InitiatingParticipantId::Nasdaq: return "Nasdaq";
        case InitiatingParticipantId::MembersExchange: return "Members Exchange";
        case InitiatingParticipantId::Iex: return "Iex";
        case InitiatingParticipantId::Cbsx: return "Cbsx";
        case InitiatingParticipantId::NasdaqPsx: return "Nasdaq Psx";
        case InitiatingParticipantId::CboeByx: return "Cboe Byx";
        case InitiatingParticipantId::CboeBzx: return "Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InitiatingParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
