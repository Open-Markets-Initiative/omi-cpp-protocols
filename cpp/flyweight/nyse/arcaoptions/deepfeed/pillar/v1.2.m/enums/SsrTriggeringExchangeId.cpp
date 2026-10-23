#include "SsrTriggeringExchangeId.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(SsrTriggeringExchangeId value) {
    switch (value) {
        case SsrTriggeringExchangeId::NyseAmerican: return "Nyse American";
        case SsrTriggeringExchangeId::NasdaqOmxBx: return "Nasdaq Omx Bx";
        case SsrTriggeringExchangeId::NyseNational: return "Nyse National";
        case SsrTriggeringExchangeId::Finra: return "Finra";
        case SsrTriggeringExchangeId::Txse: return "Txse";
        case SsrTriggeringExchangeId::N24x: return "N24X";
        case SsrTriggeringExchangeId::Ise: return "Ise";
        case SsrTriggeringExchangeId::CboeEdga: return "Cboe Edga";
        case SsrTriggeringExchangeId::CboeEdgx: return "Cboe Edgx";
        case SsrTriggeringExchangeId::Ltse: return "Ltse";
        case SsrTriggeringExchangeId::NyseTexas: return "Nyse Texas";
        case SsrTriggeringExchangeId::Nyse: return "Nyse";
        case SsrTriggeringExchangeId::NyseArca: return "Nyse Arca";
        case SsrTriggeringExchangeId::Nasdaq: return "Nasdaq";
        case SsrTriggeringExchangeId::Cts: return "Cts";
        case SsrTriggeringExchangeId::NasdaqOmx: return "Nasdaq Omx";
        case SsrTriggeringExchangeId::Iex: return "Iex";
        case SsrTriggeringExchangeId::Cbsx: return "Cbsx";
        case SsrTriggeringExchangeId::NasdaqOmxPsx: return "Nasdaq Omx Psx";
        case SsrTriggeringExchangeId::CboeByx: return "Cboe Byx";
        case SsrTriggeringExchangeId::CboeBzx: return "Cboe Bzx";
        case SsrTriggeringExchangeId::Miax: return "Miax";
        case SsrTriggeringExchangeId::Memx: return "Memx";
        case SsrTriggeringExchangeId::NoValue: return "No Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SsrTriggeringExchangeId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
