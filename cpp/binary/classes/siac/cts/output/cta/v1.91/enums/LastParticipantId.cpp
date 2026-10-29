#include "LastParticipantId.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(LastParticipantId value) {
    switch (value) {
        case LastParticipantId::NyseAmerican: return "Nyse American";
        case LastParticipantId::NasdaqBx: return "Nasdaq Bx";
        case LastParticipantId::NyseNational: return "Nyse National";
        case LastParticipantId::FinraAdf: return "Finra Adf";
        case LastParticipantId::Ise: return "Ise";
        case LastParticipantId::CboeEdga: return "Cboe Edga";
        case LastParticipantId::CboeEdgx: return "Cboe Edgx";
        case LastParticipantId::Ltse: return "Ltse";
        case LastParticipantId::NyseChicago: return "Nyse Chicago";
        case LastParticipantId::Nyse: return "Nyse";
        case LastParticipantId::NyseArca: return "Nyse Arca";
        case LastParticipantId::Cts: return "Cts";
        case LastParticipantId::Nasdaq: return "Nasdaq";
        case LastParticipantId::Iex: return "Iex";
        case LastParticipantId::Cbsx: return "Cbsx";
        case LastParticipantId::NasdaqPsx: return "Nasdaq Psx";
        case LastParticipantId::CboeByx: return "Cboe Byx";
        case LastParticipantId::CboeBzx: return "Cboe Bzx";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LastParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
