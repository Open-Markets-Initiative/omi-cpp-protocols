#include "SecurityTradingStatusReason.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(SecurityTradingStatusReason value) {
    switch (value) {
        case SecurityTradingStatusReason::None: return "None";
        case SecurityTradingStatusReason::Regulatory: return "Regulatory";
        case SecurityTradingStatusReason::Administrative: return "Administrative";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatusReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
