#include "TradingSessionSubId.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(TradingSessionSubId value) {
    switch (value) {
        case TradingSessionSubId::PreTrading: return "Pre Trading";
        case TradingSessionSubId::Trading: return "Trading";
        case TradingSessionSubId::Closing: return "Closing";
        case TradingSessionSubId::PostTrading: return "Post Trading";
        case TradingSessionSubId::PostClosing: return "Post Closing";
        case TradingSessionSubId::Quiescent: return "Quiescent";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSessionSubId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
