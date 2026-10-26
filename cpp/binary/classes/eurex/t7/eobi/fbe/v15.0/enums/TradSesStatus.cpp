#include "TradSesStatus.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

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

} // namespace eurex::t7::eobi::fbe::v15_0
