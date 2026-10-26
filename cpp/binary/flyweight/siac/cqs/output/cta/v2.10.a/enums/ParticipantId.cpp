#include "ParticipantId.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(ParticipantId value) {
    switch (value) {
        case ParticipantId::NyseAmerican: return "Nyse American";
        case ParticipantId::NasdaqOmxBx: return "Nasdaq Omx Bx";
        case ParticipantId::NyseNational: return "Nyse National";
        case ParticipantId::FinraAdf: return "Finra Adf";
        case ParticipantId::N24x: return "N24X";
        case ParticipantId::Miax: return "Miax";
        case ParticipantId::Ise: return "Ise";
        case ParticipantId::CboeEdga: return "Cboe Edga";
        case ParticipantId::CboeEdgx: return "Cboe Edgx";
        case ParticipantId::Ltse: return "Ltse";
        case ParticipantId::NyseTexas: return "Nyse Texas";
        case ParticipantId::Nyse: return "Nyse";
        case ParticipantId::NyseArca: return "Nyse Arca";
        case ParticipantId::Cqs: return "Cqs";
        case ParticipantId::Nasdaq: return "Nasdaq";
        case ParticipantId::Memx: return "Memx";
        case ParticipantId::Iex: return "Iex";
        case ParticipantId::Cbsx: return "Cbsx";
        case ParticipantId::NasdaqOmxPsx: return "Nasdaq Omx Psx";
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

} // namespace siac::cqs::output::cta::v2_10_a
