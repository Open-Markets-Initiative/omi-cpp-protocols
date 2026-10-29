#include "SsrTriggeringExchangeId.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(SsrTriggeringExchangeId value) {
    switch (value) {
        case SsrTriggeringExchangeId::NyseAmerican: return "Nyse American";
        case SsrTriggeringExchangeId::NasdaqOmxBx: return "Nasdaq Omx Bx";
        case SsrTriggeringExchangeId::NyseNational: return "Nyse National";
        case SsrTriggeringExchangeId::Finra: return "Finra";
        case SsrTriggeringExchangeId::Ise: return "Ise";
        case SsrTriggeringExchangeId::Edga: return "Edga";
        case SsrTriggeringExchangeId::Edgx: return "Edgx";
        case SsrTriggeringExchangeId::Chx: return "Chx";
        case SsrTriggeringExchangeId::Nyse: return "Nyse";
        case SsrTriggeringExchangeId::NyseArca: return "Nyse Arca";
        case SsrTriggeringExchangeId::Nasdaq: return "Nasdaq";
        case SsrTriggeringExchangeId::Cts: return "Cts";
        case SsrTriggeringExchangeId::NasdaqOmx: return "Nasdaq Omx";
        case SsrTriggeringExchangeId::Iex: return "Iex";
        case SsrTriggeringExchangeId::Cbsx: return "Cbsx";
        case SsrTriggeringExchangeId::NasdaqOmxPsx: return "Nasdaq Omx Psx";
        case SsrTriggeringExchangeId::BatsY: return "Bats Y";
        case SsrTriggeringExchangeId::Bats: return "Bats";
        case SsrTriggeringExchangeId::NoValue: return "No Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SsrTriggeringExchangeId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
