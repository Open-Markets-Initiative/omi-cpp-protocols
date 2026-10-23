#include "TradingSessionSubId.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(TradingSessionSubId value) {
    switch (value) {
        case TradingSessionSubId::PreTrading: return "Pre Trading";
        case TradingSessionSubId::Continuous: return "Continuous";
        case TradingSessionSubId::Closing: return "Closing";
        case TradingSessionSubId::PostTrading: return "Post Trading";
        case TradingSessionSubId::Quiescent: return "Quiescent";
        case TradingSessionSubId::OutOfMainSessionTrading: return "Out Of Main Session Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSessionSubId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
