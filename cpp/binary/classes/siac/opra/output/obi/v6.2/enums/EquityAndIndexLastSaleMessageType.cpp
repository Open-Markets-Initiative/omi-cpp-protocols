#include "EquityAndIndexLastSaleMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(EquityAndIndexLastSaleMessageType value) {
    switch (value) {
        case EquityAndIndexLastSaleMessageType::Canc: return "Canc";
        case EquityAndIndexLastSaleMessageType::Oseq: return "Oseq";
        case EquityAndIndexLastSaleMessageType::Cncl: return "Cncl";
        case EquityAndIndexLastSaleMessageType::Late: return "Late";
        case EquityAndIndexLastSaleMessageType::Cnco: return "Cnco";
        case EquityAndIndexLastSaleMessageType::Open: return "Open";
        case EquityAndIndexLastSaleMessageType::Cnol: return "Cnol";
        case EquityAndIndexLastSaleMessageType::Opnl: return "Opnl";
        case EquityAndIndexLastSaleMessageType::Auto: return "Auto";
        case EquityAndIndexLastSaleMessageType::Reop: return "Reop";
        case EquityAndIndexLastSaleMessageType::Ajst: return "Ajst";
        case EquityAndIndexLastSaleMessageType::Sprd: return "Sprd";
        case EquityAndIndexLastSaleMessageType::Stdl: return "Stdl";
        case EquityAndIndexLastSaleMessageType::Stpd: return "Stpd";
        case EquityAndIndexLastSaleMessageType::Cstp: return "Cstp";
        case EquityAndIndexLastSaleMessageType::Bwrt: return "Bwrt";
        case EquityAndIndexLastSaleMessageType::Cmbo: return "Cmbo";
        case EquityAndIndexLastSaleMessageType::Spim: return "Spim";
        case EquityAndIndexLastSaleMessageType::Isoi: return "Isoi";
        case EquityAndIndexLastSaleMessageType::Bnmt: return "Bnmt";
        case EquityAndIndexLastSaleMessageType::Xmpt: return "Xmpt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EquityAndIndexLastSaleMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
