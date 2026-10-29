#include "ParticipantId.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(ParticipantId value) {
    switch (value) {
        case ParticipantId::NyseAmerican: return "Nyse American";
        case ParticipantId::NasdaqBx: return "Nasdaq Bx";
        case ParticipantId::NyseNational: return "Nyse National";
        case ParticipantId::Adf: return "Adf";
        case ParticipantId::Miax: return "Miax";
        case ParticipantId::Ise: return "Ise";
        case ParticipantId::CboeEdga: return "Cboe Edga";
        case ParticipantId::CboeEdgx: return "Cboe Edgx";
        case ParticipantId::Ltse: return "Ltse";
        case ParticipantId::NyseChicago: return "Nyse Chicago";
        case ParticipantId::Nyse: return "Nyse";
        case ParticipantId::NyseArca: return "Nyse Arca";
        case ParticipantId::Cts: return "Cts";
        case ParticipantId::Nasdaq: return "Nasdaq";
        case ParticipantId::MembersExchange: return "Members Exchange";
        case ParticipantId::Iex: return "Iex";
        case ParticipantId::Cbsx: return "Cbsx";
        case ParticipantId::NasdaqPsx: return "Nasdaq Psx";
        case ParticipantId::CboeByx: return "Cboe Byx";
        case ParticipantId::CboeBzx: return "Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
