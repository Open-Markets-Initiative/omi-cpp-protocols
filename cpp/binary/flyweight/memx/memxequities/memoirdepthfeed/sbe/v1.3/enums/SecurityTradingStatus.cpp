#include "SecurityTradingStatus.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
        case SecurityTradingStatus::Halted: return "Halted";
        case SecurityTradingStatus::Paused: return "Paused";
        case SecurityTradingStatus::Quoting: return "Quoting";
        case SecurityTradingStatus::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
