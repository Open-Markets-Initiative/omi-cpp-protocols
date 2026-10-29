#include "TradSesStatus.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(TradSesStatus value) {
    switch (value) {
        case TradSesStatus::Halted: return "Halted";
        case TradSesStatus::Open: return "Open";
        case TradSesStatus::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradSesStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
