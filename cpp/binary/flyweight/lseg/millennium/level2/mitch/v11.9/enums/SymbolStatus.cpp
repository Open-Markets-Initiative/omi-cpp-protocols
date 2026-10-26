#include "SymbolStatus.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(SymbolStatus value) {
    switch (value) {
        case SymbolStatus::Active: return "Active";
        case SymbolStatus::Suspended: return "Suspended";
        case SymbolStatus::Inactive: return "Inactive";
        case SymbolStatus::Halt: return "Halt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SymbolStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::millennium::level2::mitch::v11_9
