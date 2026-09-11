#include "OperationalHaltStatus.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

std::string_view to_string(OperationalHaltStatus value) {
    switch (value) {
        case OperationalHaltStatus::IexSpecificOperationalTradingHalt: return "Iex Specific Operational Trading Halt";
        case OperationalHaltStatus::NotOperationallyHaltedOnIex: return "Not Operationally Halted On Iex";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OperationalHaltStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::iextp::v1_56
