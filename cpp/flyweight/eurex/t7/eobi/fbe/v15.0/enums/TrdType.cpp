#include "TrdType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(TrdType value) {
    switch (value) {
        case TrdType::BlockTrade: return "Block Trade";
        case TrdType::Efp: return "Efp";
        case TrdType::Efs: return "Efs";
        case TrdType::Otc: return "Otc";
        case TrdType::ExchangeBasisFacility: return "Exchange Basis Facility";
        case TrdType::VolaTrade: return "Vola Trade";
        case TrdType::EfpFinTrade: return "Efp Fin Trade";
        case TrdType::EfpIndexFuturesTrade: return "Efp Index Futures Trade";
        case TrdType::BlockTradeAtMarket: return "Block Trade At Market";
        case TrdType::XetraEurexEnlightTriggeredTrade: return "Xetra Eurex Enlight Triggered Trade";
        case TrdType::BlockQtpipTrade: return "Block Qtpip Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TrdType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
