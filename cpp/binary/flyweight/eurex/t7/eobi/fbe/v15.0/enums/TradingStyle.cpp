#include "TradingStyle.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(TradingStyle value) {
    switch (value) {
        case TradingStyle::Regular: return "Regular";
        case TradingStyle::Trftac: return "Trftac";
        case TradingStyle::Trftam: return "Trftam";
        case TradingStyle::Moc: return "Moc";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStyle value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
