#include "TesTradSesStatus.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(TesTradSesStatus value) {
    switch (value) {
        case TesTradSesStatus::Halted: return "Halted";
        case TesTradSesStatus::Open: return "Open";
        case TesTradSesStatus::Closed: return "Closed";
        case TesTradSesStatus::PreClose: return "Pre Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TesTradSesStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
